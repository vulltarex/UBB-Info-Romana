package repository;

import domain.User;
import util.paging.Page;
import util.paging.Pageable;

/**
 * Friendship repository that can return the friends of a user one page at a time.
 */
public interface FriendshipPagingRepository extends FriendshipRepository {
    /**
     * Returns the friends of a user on the requested page, ordered by identifier.
     * @param userId the identifier of the user whose friends are listed
     * @param pageable the requested page number and size
     * @return the requested page of friends; empty when the user has no friends or the page is past the last one
     * @throws IllegalArgumentException if userId or pageable is null
     * @throws RepositoryException if persistence fails
     */
    Page<User> findFriendsOnPage(Long userId, Pageable pageable);
}
