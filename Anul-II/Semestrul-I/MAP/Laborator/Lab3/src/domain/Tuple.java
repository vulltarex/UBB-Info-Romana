package domain;

import java.util.Objects;

/**
 * Immutable ordered pair used as a composite identifier.
 * @param <A> the first element type
 * @param <B> the second element type
 */
public final class Tuple<A, B> {
    private final A first;
    private final B second;

    /**
     * Creates a Tuple instance.
     * @param first the first element, possibly null
     * @param second the second element, possibly null
     */
    public Tuple(A first, B second) {
        this.first = first;
        this.second = second;
    }

    /**
     * Returns the first tuple element.
     * @return the first element
     */
    public A getFirst() {
        return first;
    }

    /**
     * Returns the second tuple element.
     * @return the second element
     */
    public B getSecond() {
        return second;
    }

    /**
     * @param o the object to compare
     * @return true when both elements are equal in the same order
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Tuple<?, ?>)) return false;
        Tuple<?, ?> other = (Tuple<?, ?>) o;
        return Objects.equals(first, other.first) && Objects.equals(second, other.second);
    }

    /** @return a hash code based on both elements */
    @Override
    public int hashCode() {
        return Objects.hash(first, second);
    }

    /** @return a readable representation of the pair */
    @Override
    public String toString() {
        return "(" + first + ", " + second + ")";
    }
}
