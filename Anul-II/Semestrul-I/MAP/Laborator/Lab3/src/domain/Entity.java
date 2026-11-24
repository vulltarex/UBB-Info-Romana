package domain;

import java.util.Objects;

/**
 * Base entity identified by an ID that must remain stable after insertion.
 * @param <ID> the identifier type
 */
public class Entity<ID> {
    private ID id;

    /** Creates an entity without an identifier. */
    public Entity() {}

    /**
     * Creates a Entity instance.
     * @param id the initial identifier
     */
    public Entity(ID id) {
        this.id = id;
    }

    /**
     * Returns the entity identifier.
     * @return the identifier, or null before assignment
     */
    public ID getID() {
        return id;
    }

    /**
     * Assigns the entity identifier.
     * @param id the identifier; do not change it after insertion into a repository
     */
    public void setId(ID id) {
        this.id = id;
    }

    /**
     * @param o the object to compare
     * @return true for the same object, or the same entity type with the same non-null ID
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || o.getClass() != getClass()) return false;
        Entity<?> other = (Entity<?>) o;
        return id != null && Objects.equals(id, other.id);
    }

    /** @return a hash code based on the identifier */
    @Override
    public int hashCode() {
        return Objects.hashCode(id);
    }
}
