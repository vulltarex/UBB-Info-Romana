package repository;

import domain.Friendship;
import domain.Tuple;

/** Persistence contract for friendships identified by their canonical participant pair. */
public interface FriendshipRepository extends Repository<Tuple<Long, Long>, Friendship> {
}
