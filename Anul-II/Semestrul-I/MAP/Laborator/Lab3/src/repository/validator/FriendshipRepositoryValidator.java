package repository.validator;

import domain.Friendship;
import domain.validator.ValidationException;
import domain.validator.Validator;
import repository.UserRepository;

/** Adds referential validation to the domain strategy without coupling domain to persistence. */
public class FriendshipRepositoryValidator implements Validator<Friendship> {
    private final Validator<Friendship> validator;
    private final UserRepository userRepo;

    /**
     * Creates a FriendshipRepositoryValidator instance.
     * @param validator the domain validation strategy
     * @param userRepo the already loaded users
     * @throws IllegalArgumentException if either dependency is null
     */
    public FriendshipRepositoryValidator(Validator<Friendship> validator, UserRepository userRepo) {
        if (validator == null || userRepo == null) throw new IllegalArgumentException("Dependentele nu pot fi null!");
        this.validator = validator;
        this.userRepo = userRepo;
    }

    /**
     * Checks the rules for the supplied entity.
     * @param entity the friendship to validate
     * @throws ValidationException if domain rules fail or a participant does not exist
     * @throws repository.RepositoryException if participant lookup fails
     * @throws UnsupportedOperationException if participant lookup is not implemented
     */
    @Override
    public void validate(Friendship entity) {
        validator.validate(entity);
        if (userRepo.findOne(entity.getFirstUserId()) == null || userRepo.findOne(entity.getSecondUserId()) == null) {
            throw new ValidationException("Prietenia trebuie sa fie intre utilizatori existenti!");
        }
    }
}
