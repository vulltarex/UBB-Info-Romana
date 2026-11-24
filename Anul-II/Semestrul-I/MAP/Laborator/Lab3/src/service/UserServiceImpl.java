package service;

import domain.Friendship;
import domain.Tuple;
import domain.User;
import repository.FriendshipRepository;
import repository.PagingRepository;
import repository.UserRepository;
import util.paging.Page;
import util.paging.Pageable;

import util.Streams;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/** User operations; storage generates identifiers. */
public class UserServiceImpl implements Service<User> {
    private final UserRepository userRepo;
    private final FriendshipRepository friendshipRepo;

    /**
     * Creates a UserService instance.
     * @param userRepo the users repository
     * @param friendshipRepo the friendships repository
     * @throws IllegalArgumentException if a repository dependency is null
     */
    public UserServiceImpl(UserRepository userRepo, FriendshipRepository friendshipRepo) {
        if (userRepo == null || friendshipRepo == null) {
            throw new IllegalArgumentException("Repository-urile nu pot fi null!");
        }
        this.userRepo = userRepo;
        this.friendshipRepo = friendshipRepo;
    }

    /**
     * Creates and saves a user, delegating identifier generation to the storage.
     * @param firstName the first name
     * @param lastName the last name
     * @return the saved user with its generated identifier
     * @throws domain.validator.ValidationException if the user is invalid
     * @throws ServiceException if saving fails or the user already exists
     * @throws repository.RepositoryException if persistence fails
     */
    public User addUser(String firstName, String lastName) {
        User user = new User(firstName, lastName);
        if (userRepo.save(user) != null) {
            throw new ServiceException("Utilizatorul exista deja!");
        }
        return user;
    }

    /**
     * Removes friendships before their user, preventing dangling references.
     * @param id the user ID
     * @throws IllegalArgumentException if id is null
     * @throws ServiceException if the user does not exist
     * @throws repository.RepositoryException if persistence fails
     */
    public void deleteUser(Long id) {
        findOne(id);
        List<Tuple<Long, Long>> ids = Streams.stream(friendshipRepo.findAll())
                .filter(friendship -> friendship.involves(id))
                .map(Friendship::getID)
                .collect(Collectors.toList());
        ids.forEach(friendshipRepo::delete);
        userRepo.delete(id);
    }

    /**
     * Replaces an existing user.
     * @param entity the replacement user, with the existing ID
     * @throws IllegalArgumentException if entity or its ID is null
     * @throws ServiceException if the user does not exist
     * @throws domain.validator.ValidationException if its data is invalid
     * @throws repository.RepositoryException if persistence fails
     */
    public void updateUser(User entity) {
        if (entity == null) throw new IllegalArgumentException("Utilizatorul nu poate fi null!");
        findOne(entity.getID());
        if (userRepo.update(entity) != null) throw new ServiceException("Utilizatorul nu exista!");
    }

    /**
     * Finds an entity by its identifier.
     * @param id the user ID
     * @return the matching user
     * @throws IllegalArgumentException if id is null
     * @throws ServiceException if the user does not exist
     * @throws repository.RepositoryException if lookup fails
     */
    public User findOne(Long id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null!");
        return Optional.ofNullable(userRepo.findOne(id))
                .orElseThrow(() -> new ServiceException("Utilizatorul nu exista!"));
    }

    /** {@inheritDoc} */
    @Override
    public Iterable<User> findAll() {
        return userRepo.findAll();
    }

    /**
     * Tells whether the configured users repository supports paging (only the database one does).
     * @return true if users can be listed page by page
     */
    public boolean supportsPaging() {
        return userRepo instanceof PagingRepository;
    }

    /**
     * Returns one page of users ordered by identifier.
     * @param pageNumber the zero-based page number
     * @param pageSize the maximum number of users on a page
     * @return the requested page; empty when the page is past the last one
     * @throws IllegalArgumentException if pageNumber is negative or pageSize is not positive
     * @throws ServiceException if the configured repository does not support paging
     * @throws repository.RepositoryException if persistence fails
     */
    public Page<User> findAllOnPage(int pageNumber, int pageSize) {
        if (pageNumber < 0 || pageSize <= 0) {
            throw new IllegalArgumentException("Numarul paginii trebuie sa fie >= 0, iar marimea paginii > 0!");
        }
        if (!(userRepo instanceof PagingRepository)) {
            throw new ServiceException("Paginarea este disponibila doar pentru repository.type=DATABASE!");
        }
        @SuppressWarnings("unchecked")
        PagingRepository<Long, User> pagingRepo = (PagingRepository<Long, User>) userRepo;
        return pagingRepo.findAllOnPage(new Pageable(pageNumber, pageSize));
    }
}