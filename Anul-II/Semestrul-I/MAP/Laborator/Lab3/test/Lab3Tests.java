import config.ConfigLoader;
import config.ConfigurationException;
import domain.Entity;
import domain.Friendship;
import domain.Tuple;
import domain.User;
import domain.UserCriteria;
import domain.validator.FriendshipValidator;
import domain.validator.UserValidator;
import domain.validator.ValidationException;
import domain.validator.Validator;
import repository.FriendshipRepository;
import repository.UserRepository;
import repository.RepositoryException;
import repository.factory.RepositoryFactory;
import service.CommunityService;
import service.FriendshipService;
import service.ServiceException;
import service.UserServiceImpl;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Set;
import java.util.function.Predicate;
import java.util.stream.Collectors;

/** Standalone integration checks; run through scripts/check.sh in a temporary directory. */
public class Lab3Tests {
    private static int checks = 0;

    private static class Context {
        private UserRepository users;
        private FriendshipRepository friendships;
        private UserServiceImpl userServiceImpl;
        private FriendshipService friendshipService;
        private CommunityService communities;

        Context(String type, String name) {
            RepositoryFactory factory = new RepositoryFactory(properties(type, name));
            users = factory.createUserRepository(new UserValidator());
            friendships = factory.createFriendshipRepository(new FriendshipValidator());
            userServiceImpl = new UserServiceImpl(users, friendships);
            friendshipService = new FriendshipService(users, friendships);
            communities = new CommunityService(users, friendships);
        }
    }

    private static Properties properties(String type, String name) {
        Properties properties = new Properties();
        properties.setProperty("repository.type", type);
        properties.setProperty("file.utilizatori", "data/" + name + "/utilizatori.txt");
        properties.setProperty("file.prietenii", "data/" + name + "/prietenii.txt");
        properties.setProperty("db.url", "not-a-real-connection");
        properties.setProperty("db.user", "test");
        properties.setProperty("db.password", "test");
        return properties;
    }

    private static void check(boolean condition, String message) {
        checks++;
        if (!condition) throw new AssertionError(message);
    }

    private static int count(Iterable<?> entities) {
        int result = 0;
        for (Object entity : entities) result++;
        return result;
    }

    private static void write(String filename, String text) throws IOException {
        Files.createDirectories(Paths.get(filename).getParent());
        Files.writeString(Paths.get(filename), text, StandardCharsets.UTF_8);
    }

    private static void identity() {
        Entity<Long> first = new Entity<>(1L);
        Entity<Long> second = new Entity<>(1L);
        check(first.equals(second) && first.hashCode() == second.hashCode(), "Entity equality/hashCode");
        check(!first.equals(null) && !first.equals("1"), "Entity type safety");
        check(!new Entity<Long>().equals(new Entity<Long>()), "Unassigned entities differ");
        User user = new User("Ana", "Pop");
        user.setId(1L);
        check(!first.equals(user) && !user.equals(first), "Entity subclass symmetry");
        Tuple<Long, Long> a = new Tuple<>(null, 2L);
        Tuple<Long, Long> b = new Tuple<>(null, 2L);
        check(a.equals(b) && a.hashCode() == b.hashCode(), "Tuple null elements");
        check(!a.equals(null) && !a.equals("pair"), "Tuple type safety");
        LocalDateTime date = LocalDateTime.of(2026, 10, 19, 10, 30);
        Friendship f1 = new Friendship(1L, 2L, date);
        Friendship f2 = new Friendship(2L, 1L, date.plusDays(1));
        check(f1.equals(f2) && f1.hashCode() == f2.hashCode(), "Canonical friendship identity");
        f2.setId(new Tuple<>(4L, 3L));
        check(f2.getID().equals(new Tuple<>(3L, 4L)), "Setter normalizes friendship ID");
    }

    private static void operations(String type) {
        Context c = new Context(type, "operations-" + type);
        check(c.communities.countCommunities() == 0, "Empty network");
        check(c.communities.mostSociableCommunity().isEmpty(), "Empty most sociable community");
        for (int i = 1; i <= 12; i++) c.userServiceImpl.addUser("Ana", "Popescu");
        check(c.communities.countCommunities() == 12, "Isolated users");
        for (long i = 1; i < 5; i++) c.friendshipService.addFriendship(i, i + 1);
        for (long i = 7; i <= 11; i++) c.friendshipService.addFriendship(6L, i);
        check(c.communities.countCommunities() == 3, "Chain, star and isolated user");
        check(c.communities.mostSociableCommunity().size() == 5, "Longest path wins over larger star");
        check(c.friendships.findOne(Friendship.createID(2L, 1L)) != null, "Canonical lookup");
        try {
            c.friendshipService.addFriendship(2L, 1L);
            throw new AssertionError("Reversed duplicate accepted");
        } catch (ServiceException e) {
            check(count(c.friendships.findAll()) == 9, "Duplicate does not change repository");
        }
        try {
            c.friendshipService.addFriendship(1L, 1L);
            throw new AssertionError("Self friendship accepted");
        } catch (ValidationException e) {
            check(true, "Self friendship rejected");
        }
        try {
            c.friendshipService.addFriendship(1L, 999L);
            throw new AssertionError("Missing participant accepted");
        } catch (ServiceException e) {
            check(true, "Service checks participant existence");
        }
        try {
            c.friendships.save(new Friendship(1L, 999L, LocalDateTime.now()));
            throw new AssertionError("Direct orphan insertion accepted");
        } catch (ValidationException e) {
            check(true, "Repository also checks participant existence");
        }
        c.friendshipService.deleteFriendship(2L, 1L);
        check(count(c.friendships.findAll()) == 8, "Reverse deletion");
        c.userServiceImpl.deleteUser(6L);
        check(count(c.friendships.findAll()) == 3 && c.users.findOne(6L) == null, "Cascade deletion");
        check(c.communities.countCommunities() == 8, "Communities after deletion");
        c.friendshipService.addFriendship(2L, 4L);
        check(c.communities.mostSociableCommunity().size() == 4, "Cycle terminates correctly");
        User updated = new User("Ștefan", "Ionescu");
        updated.setId(2L);
        c.userServiceImpl.updateUser(updated);
        check(c.users.findOne(2L).getFirstName().equals("Ștefan"), "User update");
        Friendship replacement = new Friendship(2L, 3L, LocalDateTime.of(2020, 1, 2, 3, 4));
        check(c.friendships.update(replacement) == null, "Friendship update");
        check(c.friendships.findOne(replacement.getID()).getFriendsFrom().equals(replacement.getFriendsFrom()), "Date update");
        if (type.equals("FILE")) {
            Context restarted = new Context(type, "operations-" + type);
            check(restarted.users.findOne(2L).getFirstName().equals("Ștefan"), "UTF-8 survives restart");
            check(count(restarted.friendships.findAll()) == 4, "Friendships survive restart");
            check(restarted.friendships.findOne(replacement.getID()).getFriendsFrom().equals(replacement.getFriendsFrom()), "Dates survive restart");
            restarted.userServiceImpl.addUser("Maria", "Pop");
            check(restarted.users.findOne(13L) != null, "IDs continue after restart");
            String text;
            try {
                text = Files.readString(Paths.get("data/operations-FILE/prietenii.txt"), StandardCharsets.UTF_8);
            } catch (IOException e) {
                throw new AssertionError("Cannot inspect saved text", e);
            }
            check(text.contains("2;3;2020-01-02T03:04"), "Required friendship text format");
        } else {
            check(count(new Context(type, "operations-" + type).users.findAll()) == 0, "Memory is volatile");
        }
        contracts(c);
    }

    private static void composedValidation() {
        List<String> calls = new ArrayList<>();
        Validator<User> base = new UserValidator();
        Validator<User> shortLastName = user -> {
            calls.add("extra");
            if (user.getLastName().length() > 6) throw new ValidationException("Last name is too long for the demo");
        };
        Validator<User> composed = base.andThen(shortLastName);
        User user = new User("Ana", "Pop");
        user.setId(1L);
        composed.validate(user);
        check(calls.equals(List.of("extra")), "Additional lambda runs for valid input");

        user.setLastName("Popescu");
        base.validate(user);
        try {
            composed.validate(user);
            throw new AssertionError("Additional rule did not reject the user");
        } catch (ValidationException e) {
            check(e.getMessage().equals("Last name is too long for the demo"), "New rule is independent of the base validator");
        }

        calls.clear();
        user.setFirstName("");
        try {
            composed.validate(user);
            throw new AssertionError("Invalid first name accepted");
        } catch (ValidationException e) {
            check(calls.isEmpty(), "Base validation short-circuits the additional rule");
        }
    }

    private static void queries(String type) {
        Context c = new Context(type, "queries-" + type);
        c.userServiceImpl.addUser("Ana", "Pop");
        c.userServiceImpl.addUser("Ion", "Pop");
        c.userServiceImpl.addUser("Alina", "Ionescu");
        c.userServiceImpl.addUser("Adrian", "Pop");
        Predicate<User> namedPop = UserCriteria.lastNameIs("Pop");
        Predicate<User> startsWithA = UserCriteria.firstNameStartsWith("A");
        List<User> matches = c.users.findAll(namedPop.and(startsWithA));
        Comparator<User> byName = Comparator.comparing(User::getLastName).thenComparing(User::getFirstName);
        check(matches.stream().sorted(byName).map(User::getFirstName).collect(Collectors.joining(", "))
                .equals("Adrian, Ana"), "Composed AND and sorted result");
        check(c.users.findAll(namedPop.or(startsWithA)).size() == 4, "Composed OR");
        check(c.users.findAll(namedPop.negate()).get(0).getID().equals(3L), "Negated last name");
        List<User> otherUsers = c.users.findAll(Predicate.not(startsWithA));
        check(otherUsers.size() == 1 && otherUsers.get(0).getID().equals(2L), "Predicate.not");
        check(c.users.findAll(UserCriteria.firstNameStartsWith("Z")).isEmpty(), "Empty query");
        check(matches.stream().allMatch(namedPop) && matches.stream().noneMatch(Predicate.not(startsWithA)),
                "Every result satisfies both conditions");
        check(matches.stream().anyMatch(UserCriteria.firstNameStartsWith("Adr")), "Any match");
        check(matches.stream().collect(Collectors.toMap(User::getID, User::getFirstName))
                .equals(Map.of(1L, "Ana", 4L, "Adrian")), "Filtered users indexed by identifier");

        Map<String, Long> usersPerLastName = c.users.findAll(user -> true).stream()
                .collect(Collectors.groupingBy(User::getLastName, Collectors.counting()));
        check(usersPerLastName.equals(Map.of("Pop", 3L, "Ionescu", 1L)), "Grouped query counts");
        check(usersPerLastName.values().stream().reduce(Long::sum).orElse(0L) == 4, "Grouped counts cover all users");
        check(matches.stream().min(byName.reversed()).map(User::getFirstName).orElse("").equals("Ana"),
                "Reversed comparator and optional minimum");

        c.friendshipService.addFriendship(2L, 1L);
        c.friendshipService.addFriendship(1L, 3L);
        check(c.friendshipService.findFriends(1L).stream().map(User::getID).collect(Collectors.toSet())
                .equals(Set.of(2L, 3L)), "Friends on both sides of the canonical pair");
        check(c.friendshipService.findFriends(2L).stream().map(User::getID).findFirst().orElse(-1L) == 1L,
                "Find friend from the second participant");
        check(c.friendshipService.findFriends(4L).isEmpty(), "Isolated user has no friends");
        try {
            c.friendshipService.findFriends(99L);
            throw new AssertionError("Missing user accepted by friend query");
        } catch (ServiceException e) {
            check(e.getMessage().contains("99"), "Friend query identifies the missing user");
        }

        c.friendshipService.deleteFriendship(1L, 3L);
        c.friendshipService.addFriendship(3L, 4L);
        check(c.communities.mostSociableCommunity().stream().map(User::getID).collect(Collectors.toList())
                .equals(List.of(1L, 2L)), "Equal scores keep the first Lab 3 component in DFS order");
    }

    private static void contracts(Context c) {
        for (int operation = 0; operation < 5; operation++) {
            try {
                switch (operation) {
                    case 0: c.users.findOne(null); break;
                    case 1: c.users.delete(null); break;
                    case 2: c.users.save(null); break;
                    case 3: c.users.update(null); break;
                    case 4: c.users.save(new User("Ana", "Pop")); break;
                    default: throw new AssertionError("Unknown operation");
                }
                throw new AssertionError("Null argument accepted");
            } catch (IllegalArgumentException e) {
                check(true, "Null argument contract");
            }
        }
        User duplicate = new User("Ion", "Pop");
        duplicate.setId(1L);
        check(c.users.save(duplicate) == duplicate, "Duplicate save return contract");
        User missing = new User("Ion", "Pop");
        missing.setId(999L);
        check(c.users.update(missing) == missing, "Missing update return contract");
        check(c.users.delete(999L) == null, "Missing delete return contract");
        for (String invalid : new String[] {"", "   ", null, "Ana;Ion", "Ana123"}) {
            try {
                c.userServiceImpl.addUser(invalid, "Pop");
                throw new AssertionError("Invalid name accepted");
            } catch (ValidationException e) {
                check(true, "Invalid name rejected");
            }
        }
        try {
            c.friendships.save(new Friendship(1L, 2L, null));
            throw new AssertionError("Null date accepted");
        } catch (ValidationException e) {
            check(true, "Null date rejected");
        }
    }

    private static void corruptedFiles() throws IOException {
        String[][] cases = {
            {"bad-number", "1;Ana;Pop\nabc;Ion;Pop\n", "", "NumberFormatException"},
            {"empty-name", "1;Ana;Pop\n2;Ion;\n", "", "ValidationException"},
            {"duplicate-user", "1;Ana;Pop\n1;Ion;Pop\n", "", "IllegalArgumentException"},
            {"bad-date", "1;Ana;Pop\n2;Ion;Pop\n", "\n1;2;invalid\n", "DateTimeParseException"},
            {"orphan", "1;Ana;Pop\n", "\n1;999;2026-10-19T10:30\n", "ValidationException"},
            {"duplicate-pair", "1;Ana;Pop\n2;Ion;Pop\n", "1;2;2026-10-19T10:30\n2;1;2026-10-19T10:30\n", "IllegalArgumentException"},
            {"missing-date", "1;Ana;Pop\n2;Ion;Pop\n", "\n1;2;\n", "DateTimeParseException"}
        };
        for (String[] item : cases) {
            String folder = "data/" + item[0] + "/";
            write(folder + "utilizatori.txt", item[1]);
            write(folder + "prietenii.txt", item[2]);
            try {
                new Context("FILE", item[0]);
                throw new AssertionError("Corrupt file accepted: " + item[0]);
            } catch (RepositoryException e) {
                check(e.getMessage().contains("linia 2"), "Corrupt line number: " + item[0]);
                check(e.getCause().getClass().getSimpleName().equals(item[3]), "Exception chaining: " + item[0]);
            }
        }
        String encodingDirectory = "data/bad-encoding/";
        Files.createDirectories(Paths.get(encodingDirectory));
        Files.write(Paths.get(encodingDirectory + "utilizatori.txt"), new byte[] {(byte) 0xc3, 0x28});
        try {
            new Context("FILE", "bad-encoding");
            throw new AssertionError("Invalid UTF-8 accepted");
        } catch (RepositoryException e) {
            check(e.getCause() instanceof IOException && e.getMessage().contains("utilizatori.txt"),
                    "Lazy file-read errors retain their I/O cause and path");
        }
        write("data/reversed/utilizatori.txt", "1;Ana;Pop\n2;Ion;Pop\n");
        write("data/reversed/prietenii.txt", "2;1;2026-10-19T10:30\n");
        Context reversed = new Context("FILE", "reversed");
        check(reversed.friendships.findOne(new Tuple<>(1L, 2L)) != null, "Normalization during loading");
        Context missing = new Context("FILE", "missing");
        check(!Files.exists(Paths.get("data/missing/utilizatori.txt")), "Missing file stays absent before save");
        missing.userServiceImpl.addUser("Ana", "Pop");
        check(Files.exists(Paths.get("data/missing/utilizatori.txt")), "First save creates file and directory");
        Context failedWrite = new Context("FILE", "blocked");
        write("data/blocked", "not a directory");
        try {
            failedWrite.userServiceImpl.addUser("Ana", "Pop");
            throw new AssertionError("Write into blocked directory succeeded");
        } catch (RepositoryException e) {
            check(e.getCause() instanceof IOException, "Write exception cause");
            check(count(failedWrite.users.findAll()) == 0, "Failed save rolls back memory");
        }
    }

    private static void configurationAndDatabase() {
        check(ConfigLoader.load().getProperty("repository.type") != null, "Properties resource loaded");
        Properties[] invalid = {
            new Properties(), properties("UNKNOWN", "x"), properties("FILE", "x"),
            properties("DATABASE", "x"), properties("FILE", "x")
        };
        invalid[2].remove("file.utilizatori");
        invalid[3].remove("db.password");
        invalid[4].setProperty("file.prietenii", invalid[4].getProperty("file.utilizatori"));
        for (Properties item : invalid) {
            try {
                new RepositoryFactory(item);
                throw new AssertionError("Invalid configuration accepted");
            } catch (ConfigurationException e) {
                check(!e.getMessage().isBlank(), "Clear configuration error");
            }
        }
        RepositoryFactory factory = new RepositoryFactory(properties("DATABASE", "db"));
        UserRepository users = factory.createUserRepository(new UserValidator());
        FriendshipRepository friends = factory.createFriendshipRepository(new FriendshipValidator());
        check(users.getClass().getSimpleName().equals("UserDbRepository"), "Database users selected");
        check(friends.getClass().getSimpleName().equals("FriendshipDbRepository"), "Database friendships selected");
        try {
            users.findOne(null);
            throw new AssertionError("null id accepted");
        } catch (IllegalArgumentException e) {
            check(true, "Database users rejects null ID");
        }
        try {
            friends.findOne(null);
            throw new AssertionError("null id accepted");
        } catch (IllegalArgumentException e) {
            check(true, "Database friendships rejects null ID");
        }
        check(factory.createUserRepository(new UserValidator()) == users, "Factory reuses users");
        check(factory.createFriendshipRepository(new FriendshipValidator()) == friends, "Factory reuses friendships");
    }

    /**
     * @param args unused
     * @throws IOException if temporary test data cannot be prepared
     */
    public static void main(String[] args) throws IOException {
        identity();
        operations("MEMORY");
        operations("FILE");
        corruptedFiles();
        configurationAndDatabase();
        composedValidation();
        queries("MEMORY");
        queries("FILE");
        System.out.println("Au trecut " + checks + " verificari pentru laboratoarele 3 si 4.");
    }
}
