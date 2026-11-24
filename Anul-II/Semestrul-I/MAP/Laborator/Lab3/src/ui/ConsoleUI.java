package ui;

import config.ConfigLoader;
import config.ConfigurationException;
import domain.Friendship;
import domain.User;
import domain.validator.FriendshipValidator;
import domain.validator.UserValidator;
import domain.validator.ValidationException;
import domain.validator.Validator;
import repository.FriendshipRepository;
import repository.RepositoryException;
import repository.UserRepository;
import repository.factory.RepositoryFactory;
import service.CommunityService;
import service.FriendshipService;
import service.ServiceException;
import service.UserServiceImpl;

import util.paging.Page;

import java.util.List;
import java.util.Properties;
import java.util.Scanner;
import java.util.function.IntFunction;

/** Console interface and application boundary for reporting recoverable errors. */
public class ConsoleUI {
    private static final int DEFAULT_PAGE_SIZE = 5;
    private UserServiceImpl userServiceImpl;
    private FriendshipService friendshipService;
    private CommunityService communityService;
    private final int pageSize;
    private Scanner scanner = new Scanner(System.in);

    /**
     * Creates a ConsoleUI instance with the default page size.
     * @param userServiceImpl the user operations
     * @param friendshipService the friendship operations
     * @param communityService the community queries
     */
    public ConsoleUI(UserServiceImpl userServiceImpl, FriendshipService friendshipService, CommunityService communityService) {
        this(userServiceImpl, friendshipService, communityService, DEFAULT_PAGE_SIZE);
    }

    /**
     * Creates a ConsoleUI instance.
     * @param userServiceImpl the user operations
     * @param friendshipService the friendship operations
     * @param communityService the community queries
     * @param pageSize the number of elements shown on a page when paging is available
     */
    public ConsoleUI(UserServiceImpl userServiceImpl, FriendshipService friendshipService,
                     CommunityService communityService, int pageSize) {
        this.userServiceImpl = userServiceImpl;
        this.friendshipService = friendshipService;
        this.communityService = communityService;
        this.pageSize = pageSize;
    }

    /**
     * Reads the page size from the page.size property, using a default when it is missing.
     * @param config the loaded configuration
     * @return a positive page size
     * @throws ConfigurationException if page.size is not a positive integer
     */
    private static int readPageSize(Properties config) {
        String value = config.getProperty("page.size");
        if (value == null || value.isBlank()) return DEFAULT_PAGE_SIZE;
        try {
            int size = Integer.parseInt(value.trim());
            if (size <= 0) throw new ConfigurationException("page.size trebuie sa fie un numar pozitiv!");
            return size;
        } catch (NumberFormatException e) {
            throw new ConfigurationException("page.size trebuie sa fie un numar intreg!", e);
        }
    }

    /**
     * Builds application dependencies through the factory and reports startup errors.
     * Persistence selection never changes this method or the service implementations.
     */
    public static void start() {
        try {
            Properties config = ConfigLoader.load();
            int pageSize = readPageSize(config);
            RepositoryFactory factory = new RepositoryFactory(config);
            Validator<User> userValidator = new UserValidator();
            if (factory.getType() == repository.factory.RepositoryType.FILE) {
                userValidator = userValidator.andThen(user -> {
                    if (hasFieldSeparator(user.getFirstName()) || hasFieldSeparator(user.getLastName())) {
                        throw new ValidationException("Numele nu poate contine separatori de camp sau de linie!");
                    }
                });
            }
            UserRepository userRepo = factory.createUserRepository(userValidator);
            FriendshipRepository friendshipRepo = factory.createFriendshipRepository(new FriendshipValidator());
            UserServiceImpl userServiceImpl = new UserServiceImpl(userRepo, friendshipRepo);
            FriendshipService friendshipService = new FriendshipService(userRepo, friendshipRepo);
            CommunityService communityService = new CommunityService(userRepo, friendshipRepo);
            ConsoleUI ui = new ConsoleUI(userServiceImpl, friendshipService, communityService, pageSize);
            ui.run();
        } catch (ConfigurationException | RepositoryException | ValidationException | ServiceException
                 | IllegalArgumentException | UnsupportedOperationException e) {
            System.out.println("Aplicatia nu poate porni: " + e.getMessage());
        }
    }

    private static boolean hasFieldSeparator(String value) {
        return value.indexOf(';') >= 0 || value.indexOf('\n') >= 0 || value.indexOf('\r') >= 0;
    }

    private String readString(String message) {
        System.out.print(message);
        if (!scanner.hasNextLine()) throw new ServiceException("Date de intrare incomplete!");
        return scanner.nextLine();
    }

    private Long readId(String message) {
        return Long.parseLong(readString(message).trim());
    }

    private void printUser(User user) {
        System.out.println(user.getID() + " | " + user.getFirstName() + " | " + user.getLastName());
    }

    private void printFriendship(Friendship friendship) {
        System.out.println(friendship.getFirstUserId() + " - " + friendship.getSecondUserId()
                + " | " + friendship.getFriendsFrom());
    }

    /**
     * Shows users page by page; each page is requested again, so the page count stays current.
     * @param loader returns the page with the given zero-based number
     */
    private void browsePages(IntFunction<Page<User>> loader) {
        int pageNumber = 0;
        while (true) {
            Page<User> page = loader.apply(pageNumber);
            int totalPages = Math.max(1, (page.getTotalNumberOfElements() + pageSize - 1) / pageSize);
            if (pageNumber >= totalPages) {
                pageNumber = totalPages - 1;
                continue;
            }
            if (page.getTotalNumberOfElements() == 0) System.out.println("Nu exista elemente de afisat!");
            page.getElementsOnPage().forEach(this::printUser);
            System.out.println("Pagina " + (pageNumber + 1) + " din " + totalPages
                    + " (" + page.getTotalNumberOfElements() + " in total)");
            String command = readString("[u] urmatoarea, [a] anterioara, [x] inapoi la meniu: ").trim().toLowerCase();
            switch (command) {
                case "u":
                    if (pageNumber + 1 < totalPages) pageNumber++;
                    else System.out.println("Esti deja pe ultima pagina!");
                    break;
                case "a":
                    if (pageNumber > 0) pageNumber--;
                    else System.out.println("Esti deja pe prima pagina!");
                    break;
                case "x":
                    return;
                default:
                    System.out.println("Comanda invalida!");
            }
        }
    }

    private void printMenu() {
        System.out.println("\n1. Adauga utilizator");
        System.out.println("2. Sterge utilizator");
        System.out.println("3. Actualizeaza utilizator");
        System.out.println("4. Afiseaza utilizatori");
        System.out.println("5. Adauga prietenie");
        System.out.println("6. Sterge prietenie");
        System.out.println("7. Afiseaza prietenii");
        System.out.println("8. Numar de comunitati");
        System.out.println("9. Cea mai sociabila comunitate");
        System.out.println("10. Afiseaza prietenii unui utilizator");
        System.out.println("0. Iesire");
        System.out.print("Optiune: ");
    }

    /** Reads commands until exit or end of input, reporting expected operation errors. */
    public void run() {
        while (true) {
            printMenu();
            if (!scanner.hasNextLine()) return;
            String option = scanner.nextLine().trim();
            try {
                switch (option) {
                    case "1":
                        User addedUser = userServiceImpl.addUser(readString("Prenume: "), readString("Nume: "));
                        System.out.println("Utilizator adaugat cu ID-ul: " + addedUser.getID());
                        break;
                    case "2":
                        userServiceImpl.deleteUser(readId("ID utilizator: "));
                        System.out.println("Utilizator sters!");
                        break;
                    case "3":
                        Long id = readId("ID utilizator: ");
                        User user = new User(readString("Prenume nou: "), readString("Nume nou: "));
                        user.setId(id);
                        userServiceImpl.updateUser(user);
                        System.out.println("Utilizator actualizat!");
                        break;
                    case "4":
                        if (userServiceImpl.supportsPaging()) {
                            browsePages(pageNumber -> userServiceImpl.findAllOnPage(pageNumber, pageSize));
                        } else {
                            userServiceImpl.findAll().forEach(this::printUser);
                        }
                        break;
                    case "5":
                        friendshipService.addFriendship(readId("ID primul utilizator: "), readId("ID al doilea utilizator: "));
                        System.out.println("Prietenie adaugata!");
                        break;
                    case "6":
                        friendshipService.deleteFriendship(readId("ID primul utilizator: "), readId("ID al doilea utilizator: "));
                        System.out.println("Prietenie stearsa!");
                        break;
                    case "7":
                        friendshipService.findAll().forEach(this::printFriendship);
                        break;
                    case "8":
                        System.out.println("Numar de comunitati: " + communityService.countCommunities());
                        break;
                    case "9":
                        List<User> community = communityService.mostSociableCommunity();
                        if (community.isEmpty()) System.out.println("Reteaua este goala!");
                        community.forEach(this::printUser);
                        break;
                    case "10":
                        Long userId = readId("ID utilizator: ");
                        if (friendshipService.supportsPaging()) {
                            browsePages(pageNumber -> friendshipService.findFriendsOnPage(userId, pageNumber, pageSize));
                        } else {
                            List<User> friends = friendshipService.findFriends(userId);
                            if (friends.isEmpty()) System.out.println("Utilizatorul nu are prieteni!");
                            friends.forEach(this::printUser);
                        }
                        break;
                    case "0":
                        return;
                    default:
                        System.out.println("Optiune invalida!");
                }
            } catch (NumberFormatException e) {
                System.out.println("ID-ul trebuie sa fie un numar intreg de tip Long!");
            } catch (ValidationException | ServiceException | RepositoryException | IllegalArgumentException
                     | UnsupportedOperationException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
