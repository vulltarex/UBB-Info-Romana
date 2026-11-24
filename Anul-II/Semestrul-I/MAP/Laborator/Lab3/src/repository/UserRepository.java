package repository;

import domain.User;

/** Persistence contract for the user aggregate. */
public interface UserRepository extends Repository<Long, User> {
}
