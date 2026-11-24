package config;

/** Unchecked exception describing missing or invalid application configuration. */
public class ConfigurationException extends RuntimeException {
    /**
     * Creates a ConfigurationException instance.
     * @param message the configuration error
     */
    public ConfigurationException(String message) {
        super(message);
    }

    /**
     * Creates a ConfigurationException instance.
     * @param message the configuration error
     * @param cause the original failure
     */
    public ConfigurationException(String message, Throwable cause) {
        super(message, cause);
    }
}
