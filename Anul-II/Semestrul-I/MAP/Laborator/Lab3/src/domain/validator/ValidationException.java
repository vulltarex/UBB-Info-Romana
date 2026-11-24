package domain.validator;

/** Unchecked exception describing invalid domain data. */
public class ValidationException extends RuntimeException {
    /**
     * Creates a ValidationException instance.
     * @param message the validation error
     */
    public ValidationException(String message) {
        super(message);
    }
}
