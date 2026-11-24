package domain.validator;

import domain.Friendship;

/** Validates friendship IDs, distinct participants and the friendship date. */
public class FriendshipValidator implements Validator<Friendship> {
    /** Creates the friendship validation strategy. */
    public FriendshipValidator() {}

    /**
     * Checks the rules for the supplied entity.
     * @param entity the friendship to validate
     * @throws ValidationException if its participants or date are invalid
     */
    @Override
    public void validate(Friendship entity) {
        if (entity == null) throw new ValidationException("Prietenia nu poate fi null!");
        if (entity.getID() == null || entity.getFirstUserId() == null || entity.getSecondUserId() == null) {
            throw new ValidationException("ID-urile utilizatorilor nu pot fi null!");
        }
        if (entity.getFirstUserId() <= 0 || entity.getSecondUserId() <= 0) {
            throw new ValidationException("ID-urile utilizatorilor trebuie sa fie pozitive!");
        }
        if (entity.getFirstUserId().equals(entity.getSecondUserId())) {
            throw new ValidationException("Un utilizator nu poate fi prieten cu el insusi!");
        }
        if (entity.getFriendsFrom() == null) throw new ValidationException("Data prieteniei nu poate fi null!");
    }
}
