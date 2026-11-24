package repository;

import domain.Friendship;
import domain.Tuple;
import domain.validator.Validator;

/** In-memory persistence for friendships. */
public class FriendshipInMemoryRepository extends InMemoryRepository<Tuple<Long, Long>, Friendship>
        implements FriendshipRepository {
    /**
     * Creates an empty friendships repository.
     * @param validator strategy applied before saving or updating a friendship
     * @throws IllegalArgumentException if the validator is null
     */
    public FriendshipInMemoryRepository(Validator<Friendship> validator) {
        super(validator);
    }
}
