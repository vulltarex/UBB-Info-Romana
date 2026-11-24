package repository;

import domain.User;
import domain.validator.Validator;

/**
 * Text conversion for users: id;firstName;lastName with auto-generated identifiers.
 */
public class UserFileRepository extends AbstractFileRepository<Long, User> implements UserRepository {
    /**
     * Creates a UserFileRepository instance.
     * @param validator the validation strategy
     * @param filename the relative UTF-8 text file path
     * @throws IllegalArgumentException if a parameter is invalid
     * @throws RepositoryException if existing data cannot be loaded
     */
    public UserFileRepository(Validator<User> validator, String filename) {
        super(validator, filename);
    }

    /**
     * Saves a user, auto-generating an identifier if none was set.
     * @param entity the user to save
     * @return null on insertion, or the entity if its ID already exists
     * @throws IllegalArgumentException if entity is null
     */
    @Override
    public User save(User entity) {
        if (entity != null && entity.getID() == null) {
            long maxId = repo.keySet().stream().mapToLong(Long::longValue).max().orElse(0L);
            entity.setId(maxId + 1);
        }
        return super.save(entity);
    }

    /** {@inheritDoc} */
    @Override
    protected User extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length != 3) throw new IllegalArgumentException("Se asteapta id;prenume;nume!");
        User entity = new User(fields[1], fields[2]);
        entity.setId(Long.parseLong(fields[0]));
        return entity;
    }

    /** {@inheritDoc} */
    @Override
    protected String createEntityAsString(User entity) {
        return entity.getID() + ";" + entity.getFirstName() + ";" + entity.getLastName();
    }
}
