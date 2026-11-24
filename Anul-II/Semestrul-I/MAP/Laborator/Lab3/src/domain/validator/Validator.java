package domain.validator;

import java.util.Objects;

/**
 * Strategy for checking domain rules.
 * @param <T> the validated type
 */
@FunctionalInterface
public interface Validator<T> {
    /**
     * Checks the rules for the supplied entity.
     * @param entity the object to validate
     * @throws ValidationException if a domain rule is violated
     */
    void validate(T entity);

    /**
     * Composes this validator with another rule, evaluated only if this rule succeeds.
     * @param other the validator to apply second
     * @return a validator that runs both rules in order
     * @throws NullPointerException if the second validator is null
     */
    default Validator<T> andThen(Validator<T> other) {
        Objects.requireNonNull(other);
        return entity -> {
            validate(entity);
            other.validate(entity);
        };
    }
}
