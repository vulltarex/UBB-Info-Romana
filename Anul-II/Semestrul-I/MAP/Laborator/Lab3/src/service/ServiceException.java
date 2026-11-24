package service;

/** Unchecked exception describing an invalid application operation. */
public class ServiceException extends RuntimeException {
    /**
     * Creates a ServiceException instance.
     * @param message the explanation presented to the user
     */
    public ServiceException(String message) {
        super(message);
    }
}
