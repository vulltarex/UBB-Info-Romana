package repository;

import domain.User;
import domain.validator.Validator;

/**
 * In-memory persistence for users with auto-generated identifiers.
 */
public class UserInMemoryRepository extends InMemoryRepository<Long, User> implements UserRepository {
    /**
     * Creates an empty users repository.
     * @param validator strategy applied before saving or updating a user
     * @throws IllegalArgumentException if the validator is null
     */
    public UserInMemoryRepository(Validator<User> validator) {
        super(validator);
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
}