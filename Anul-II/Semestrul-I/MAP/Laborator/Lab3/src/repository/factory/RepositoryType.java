package repository.factory;

/** Persistence backends selectable through config.properties. */
public enum RepositoryType {
    /** Volatile in-memory storage. */
    MEMORY,
    /** UTF-8 text file storage. */
    FILE,
    /** Database placeholder; JDBC is implemented in laboratory 5. */
    DATABASE
}
