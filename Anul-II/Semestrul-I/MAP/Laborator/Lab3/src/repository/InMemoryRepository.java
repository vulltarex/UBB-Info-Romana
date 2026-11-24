package repository;

import domain.Entity;
import domain.validator.Validator;
import java.util.HashMap;
import java.util.Map;

/**
 * Repository that stores validated entities in a map (Strategy pattern).
 * @param <ID> the identifier type
 * @param <E> the entity type
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    /** Strategy applied before insertion and update. */
    protected final Validator<E> validator;
    /** Entities indexed by their identifiers. */
    protected final Map<ID, E> repo;

    /**
     * Creates a InMemoryRepository instance.
     * @param validator the validation strategy
     * @throws IllegalArgumentException if validator is null
     */
    public InMemoryRepository(Validator<E> validator) {
        if (validator == null) throw new IllegalArgumentException("Validatorul nu poate fi null!");
        this.validator = validator;
        repo = new HashMap<>();
    }

    /** {@inheritDoc} */
    @Override
    public E findOne(ID id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null!");
        return repo.get(id);
    }

    /** {@inheritDoc} */
    @Override
    public Iterable<E> findAll() {
        return repo.values();
    }

    /** {@inheritDoc} */
    @Override
    public E save(E entity) {
        validate(entity);
        if (repo.containsKey(entity.getID())) return entity;
        repo.put(entity.getID(), entity);
        return null;
    }

    /** {@inheritDoc} */
    @Override
    public E delete(ID id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null!");
        return repo.remove(id);
    }

    /** {@inheritDoc} */
    @Override
    public E update(E entity) {
        validate(entity);
        if (!repo.containsKey(entity.getID())) return entity;
        repo.put(entity.getID(), entity);
        return null;
    }

    private void validate(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entitatea nu poate fi null!");
        if (entity.getID() == null) throw new IllegalArgumentException("ID-ul nu poate fi null!");
        validator.validate(entity);
    }
}
