package domain;

import java.util.Objects;
import java.util.function.Predicate;

/** Reusable predicates for queries over users. */
public final class UserCriteria {
    private UserCriteria() {
    }

    /**
     * Creates a case-sensitive last-name criterion.
     * @param lastName the complete last name to match
     * @return a predicate accepting users with that last name
     * @throws NullPointerException if the last name is null
     */
    public static Predicate<User> lastNameIs(String lastName) {
        Objects.requireNonNull(lastName);
        return user -> lastName.equals(user.getLastName());
    }

    /**
     * Creates a case-sensitive first-name prefix criterion.
     * @param prefix the beginning of the first name to match
     * @return a predicate accepting users whose first name starts with the prefix
     * @throws NullPointerException if the prefix is null
     */
    public static Predicate<User> firstNameStartsWith(String prefix) {
        Objects.requireNonNull(prefix);
        return user -> user.getFirstName().startsWith(prefix);
    }
}
