package repository.factory;

import config.ConfigurationException;
import domain.Friendship;
import domain.User;
import domain.validator.Validator;
import repository.FriendshipFileRepository;
import repository.FriendshipInMemoryRepository;
import repository.FriendshipRepository;
import repository.UserFileRepository;
import repository.UserInMemoryRepository;
import repository.UserRepository;
import repository.db.FriendshipDbRepository;
import repository.db.UserDbRepository;
import repository.validator.FriendshipRepositoryValidator;

import java.nio.file.InvalidPathException;
import java.nio.file.Paths;
import java.util.Locale;
import java.util.Map;
import java.util.Properties;
import java.util.function.Function;

/** Simple Factory; the only application class that selects concrete repository classes. */
public class RepositoryFactory {
    private final Properties properties = new Properties();
    private final RepositoryType type;
    private final Map<RepositoryType, Function<Validator<User>, UserRepository>> userBuilders = Map.of(
            RepositoryType.MEMORY, UserInMemoryRepository::new,
            RepositoryType.FILE, validator -> new UserFileRepository(validator, required("file.utilizatori")),
            RepositoryType.DATABASE, validator -> new UserDbRepository(
                    validator, required("db.url"), required("db.user"), required("db.password")));
    private final Map<RepositoryType, Function<Validator<Friendship>, FriendshipRepository>> friendshipBuilders = Map.of(
            RepositoryType.MEMORY, FriendshipInMemoryRepository::new,
            RepositoryType.FILE, validator -> new FriendshipFileRepository(validator, required("file.prietenii")),
            RepositoryType.DATABASE, validator -> new FriendshipDbRepository(
                    validator, required("db.url"), required("db.user"), required("db.password")));
    private UserRepository userRepo;
    private FriendshipRepository friendshipRepo;

    /**
     * Creates a RepositoryFactory instance.
     * @param properties the configuration, copied to keep the selected backend stable
     * @throws ConfigurationException if the backend or its required parameters are invalid
     */
    public RepositoryFactory(Properties properties) {
        if (properties == null) throw new ConfigurationException("Configuratia nu poate fi null!");
        this.properties.putAll(properties);
        String value = required("repository.type");
        try {
            type = RepositoryType.valueOf(value.toUpperCase(Locale.ROOT));
        } catch (IllegalArgumentException e) {
            throw new ConfigurationException("repository.type necunoscut: " + value + ". Foloseste MEMORY, FILE sau DATABASE.", e);
        }
        if (type == RepositoryType.FILE) {
            String users = relativePath("file.utilizatori");
            String friendships = relativePath("file.prietenii");
            if (Paths.get(users).normalize().equals(Paths.get(friendships).normalize())) {
                throw new ConfigurationException("Utilizatorii si prieteniile trebuie sa foloseasca fisiere separate!");
            }
        }
        if (type == RepositoryType.DATABASE) {
            required("db.url");
            required("db.user");
            required("db.password");
        }
    }

    /**
     * Returns the selected repository type.
     * @return the configured RepositoryType
     */
    public RepositoryType getType() {
        return type;
    }

    private String required(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank()) throw new ConfigurationException("Proprietatea obligatorie " + key + " lipseste sau este vida!");
        return value.trim();
    }

    private String relativePath(String key) {
        String value = required(key);
        try {
            if (Paths.get(value).isAbsolute()) throw new ConfigurationException(key + " trebuie sa fie o cale relativa!");
        } catch (InvalidPathException e) {
            throw new ConfigurationException("Cale invalida pentru " + key + ".", e);
        }
        return value;
    }

    /**
     * Creates and caches the users repository. Subsequent calls return the same instance.
     * @param validator the user validation strategy used on first creation
     * @return the users repository for the configured backend
     * @throws IllegalArgumentException if the validator is null
     * @throws repository.RepositoryException if file data cannot be loaded
     */
    public UserRepository createUserRepository(Validator<User> validator) {
        if (validator == null) throw new IllegalArgumentException("Validatorul nu poate fi null!");
        if (userRepo != null) return userRepo;
        userRepo = userBuilders.get(type).apply(validator);
        return userRepo;
    }

    /**
     * Creates and caches friendships, validating references against this factory's users.
     * Users must be created first, before friendships are loaded from a file.
     * @param validator the domain strategy used on first creation
     * @return the friendships repository for the same configured backend
     * @throws IllegalArgumentException if the validator is null
     * @throws IllegalStateException if users have not been created first
     * @throws repository.RepositoryException if file data cannot be loaded
     */
    public FriendshipRepository createFriendshipRepository(Validator<Friendship> validator) {
        if (validator == null) throw new IllegalArgumentException("Validatorul nu poate fi null!");
        if (userRepo == null) throw new IllegalStateException("Creeaza repository-ul de utilizatori inaintea prieteniilor!");
        if (friendshipRepo != null) return friendshipRepo;
        Validator<Friendship> referenceValidator = new FriendshipRepositoryValidator(validator, userRepo);
        friendshipRepo = friendshipBuilders.get(type).apply(referenceValidator);
        return friendshipRepo;
    }
}
