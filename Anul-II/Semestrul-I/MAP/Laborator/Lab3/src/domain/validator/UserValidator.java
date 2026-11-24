package domain.validator;

import domain.User;

/**
 * Validates user names and positive identifiers when present.
 */
public class UserValidator implements Validator<User> {
    /** Creates the user validation strategy. */
    public UserValidator() {}

    /**
     * Checks the validation rules for the supplied user entity.
     * @param entity the user to validate
     * @throws ValidationException if the user, its ID when present, or names are invalid
     */
    @Override
    public void validate(User entity) {
        if (entity == null) {
            throw new ValidationException("Utilizatorul nu poate fi null!");
        }
        if (entity.getID() != null && entity.getID() <= 0) {
            throw new ValidationException("ID-ul utilizatorului trebuie sa fie pozitiv!");
        }
        validateName(entity.getFirstName(), "Prenumele");
        validateName(entity.getLastName(), "Numele");
    }

    private void validateName(String name, String field) {
        if (name == null || name.isBlank()) {
            throw new ValidationException(field + " nu poate fi vid!");
        }
    }
}
