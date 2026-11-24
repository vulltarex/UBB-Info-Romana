package service;

/**
 * Common read operation for application services.
 * @param <E> the entity type
 */
public interface Service<E> {
    /**
     * Returns all stored entities.
     * @return all entities managed by this service
     * @throws repository.RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    Iterable<E> findAll();
}
