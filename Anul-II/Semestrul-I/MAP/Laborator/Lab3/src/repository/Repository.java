package repository;

import domain.Entity;
import util.Streams;

import java.util.List;
import java.util.Objects;
import java.util.function.Predicate;
import java.util.stream.Collectors;

/**
 * Persistence contract shared by memory, file and future database implementations.
 * IDs must remain unchanged while entities are stored. Callers must not mutate returned
 * entities directly; use update instead. Database placeholders throw
 * UnsupportedOperationException for every operation until laboratory 5.
 * @param <ID> the identifier type
 * @param <E> the entity type
 */
public interface Repository<ID, E extends Entity<ID>> {
    /**
     * Finds an entity by its identifier.
     * @param id a non-null identifier; friendship IDs must be normalized
     * @return the stored entity, or null when absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    E findOne(ID id);

    /**
     * Returns all stored entities.
     * @return all stored entities; do not modify the repository during iteration
     * @throws RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    Iterable<E> findAll();

    /**
     * Collects entities that satisfy a supplied criterion.
     * @param filter a predicate evaluated against each stored entity
     * @return the matching entities in encounter order
     * @throws NullPointerException if the predicate is null
     * @throws RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    default List<E> findAll(Predicate<E> filter) {
        Objects.requireNonNull(filter);
        return Streams.stream(findAll()).filter(filter).collect(Collectors.toList());
    }

    /**
     * Validates and inserts an entity unless its ID already exists.
     * @param entity a non-null entity with a non-null ID
     * @return null on insertion, or the supplied entity if its ID already exists
     * @throws IllegalArgumentException if entity or its ID is null
     * @throws domain.validator.ValidationException if domain or reference validation fails
     * @throws RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    E save(E entity);

    /**
     * Removes an entity by its identifier.
     * @param id a non-null identifier; friendship IDs must be normalized
     * @return the removed entity, or null when absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    E delete(ID id);

    /**
     * Validates and replaces an existing entity.
     * @param entity a non-null entity with a non-null ID
     * @return null on replacement, or the supplied entity if its ID is absent
     * @throws IllegalArgumentException if entity or its ID is null
     * @throws domain.validator.ValidationException if domain or reference validation fails
     * @throws RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    E update(E entity);
}
