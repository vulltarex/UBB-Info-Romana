package repository;

/** Unchecked persistence exception that retains the original failure as its cause. */
public class RepositoryException extends RuntimeException {
    /**
     * Creates a RepositoryException instance with a descriptive message.
     * @param message the operation context or failure description
     */
    public RepositoryException(String message) {
        super(message);
    }

    /**
     * Creates a RepositoryException instance.
     * @param message the operation, file and line context when available
     * @param cause the original failure
     */
    public RepositoryException(String message, Throwable cause) {
        super(message, cause);
    }
}
