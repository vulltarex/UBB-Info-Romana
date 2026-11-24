package service;

import domain.Friendship;
import domain.User;
import repository.FriendshipPagingRepository;
import repository.FriendshipRepository;
import repository.UserRepository;
import util.Streams;
import util.paging.Page;
import util.paging.Pageable;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/** Friendship operations using canonical composite IDs. */
public class FriendshipService implements Service<Friendship> {
    private final UserRepository userRepo;
    private final FriendshipRepository friendshipRepo;

    /**
     * Creates a FriendshipService instance.
     * @param userRepo the users repository
     * @param friendshipRepo the friendships repository
     */
    public FriendshipService(UserRepository userRepo, FriendshipRepository friendshipRepo) {
        this.userRepo = userRepo;
        this.friendshipRepo = friendshipRepo;
    }

    /**
     * Creates a friendship between existing users.
     * @param firstId the first participant ID
     * @param secondId the second participant ID
     * @throws IllegalArgumentException if either ID is null
     * @throws ServiceException if a participant is absent or the friendship already exists
     * @throws domain.validator.ValidationException if the friendship is invalid
     * @throws repository.RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    public void addFriendship(Long firstId, Long secondId) {
        findUser(firstId);
        findUser(secondId);
        Friendship friendship = new Friendship(firstId, secondId, LocalDateTime.now());
        if (friendshipRepo.save(friendship) != null) throw new ServiceException("Prietenia exista deja!");
    }

    /**
     * Removes a friendship regardless of participant order.
     * @param firstId either participant ID
     * @param secondId the other participant ID
     * @throws IllegalArgumentException if either ID is null
     * @throws ServiceException if a participant or the friendship does not exist
     * @throws repository.RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    public void deleteFriendship(Long firstId, Long secondId) {
        findUser(firstId);
        findUser(secondId);
        if (friendshipRepo.delete(Friendship.createID(firstId, secondId)) == null) {
            throw new ServiceException("Prietenia nu exista!");
        }
    }

    /**
     * Finds the users connected by a friendship to the given user.
     * @param id the identifier of an existing user
     * @return the user's friends in repository encounter order
     * @throws IllegalArgumentException if the identifier is null
     * @throws ServiceException if the user or a referenced friend does not exist
     * @throws repository.RepositoryException if reading the users or friendships fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    public List<User> findFriends(Long id) {
        findUser(id);
        return Streams.stream(friendshipRepo.findAll())
                .filter(friendship -> friendship.involves(id))
                .map(friendship -> id.equals(friendship.getFirstUserId())
                        ? friendship.getSecondUserId() : friendship.getFirstUserId())
                .map(this::findUser)
                .collect(Collectors.toList());
    }

    /**
     * Tells whether the configured friendships repository supports paging (only the database one does).
     * @return true if friends can be listed page by page
     */
    public boolean supportsPaging() {
        return friendshipRepo instanceof FriendshipPagingRepository;
    }

    /**
     * Returns one page of the friends of an existing user, ordered by identifier.
     * @param id the identifier of an existing user
     * @param pageNumber the zero-based page number
     * @param pageSize the maximum number of friends on a page
     * @return the requested page; empty when the user has no friends or the page is past the last one
     * @throws IllegalArgumentException if id is null, pageNumber is negative or pageSize is not positive
     * @throws ServiceException if the user does not exist or the repository does not support paging
     * @throws repository.RepositoryException if persistence fails
     */
    public Page<User> findFriendsOnPage(Long id, int pageNumber, int pageSize) {
        if (pageNumber < 0 || pageSize <= 0) {
            throw new IllegalArgumentException("Numarul paginii trebuie sa fie >= 0, iar marimea paginii > 0!");
        }
        findUser(id);
        if (!(friendshipRepo instanceof FriendshipPagingRepository pagingRepo)) {
            throw new ServiceException("Paginarea este disponibila doar pentru repository.type=DATABASE!");
        }
        return pagingRepo.findFriendsOnPage(id, new Pageable(pageNumber, pageSize));
    }

    private User findUser(Long id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null!");
        return Optional.ofNullable(userRepo.findOne(id))
                .orElseThrow(() -> new ServiceException("Utilizatorul cu ID-ul " + id + " nu exista!"));
    }

    /** {@inheritDoc} */
    @Override
    public Iterable<Friendship> findAll() {
        return friendshipRepo.findAll();
    }
}
