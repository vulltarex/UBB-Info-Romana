package repository.db;

import domain.Friendship;
import domain.Tuple;
import domain.User;
import domain.validator.Validator;
import repository.FriendshipPagingRepository;
import repository.RepositoryException;
import util.paging.Page;
import util.paging.Pageable;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

/**
 * JDBC persistence for friendships in PostgreSQL.
 */
public class FriendshipDbRepository implements FriendshipPagingRepository {
    private final Validator<Friendship> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates a FriendshipDbRepository instance.
     * @param validator the validation strategy for friendships
     * @param url the configured connection URL
     * @param user the configured database user
     * @param password the configured database password
     * @throws IllegalArgumentException if a dependency is null
     */
    public FriendshipDbRepository(Validator<Friendship> validator, String url, String user, String password) {
        if (validator == null || url == null || user == null || password == null) {
            throw new IllegalArgumentException("Parametrii repository-ului DB nu pot fi null!");
        }
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * Finds a friendship by its participant IDs.
     * @param id the pair of user IDs
     * @return the friendship found, or null if absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if database lookup fails
     */
    @Override
    public Friendship findOne(Tuple<Long, Long> id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        Tuple<Long, Long> normalized = Friendship.createID(id.getFirst(), id.getSecond());
        String sql = "SELECT id1, id2, friends_from FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, normalized.getFirst());
            ps.setLong(2, normalized.getSecond());
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    Timestamp ts = rs.getTimestamp("friends_from");
                    return new Friendship(rs.getLong("id1"), rs.getLong("id2"), ts.toLocalDateTime());
                }
                return null;
            }
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "cautarea prieteniei");
        }
    }

    /**
     * Returns all stored friendships.
     * @return list of all friendships
     * @throws RepositoryException if database query fails
     */
    @Override
    public Iterable<Friendship> findAll() {
        List<Friendship> list = new ArrayList<>();
        String sql = "SELECT id1, id2, friends_from FROM friendships";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                Timestamp ts = rs.getTimestamp("friends_from");
                list.add(new Friendship(rs.getLong("id1"), rs.getLong("id2"), ts.toLocalDateTime()));
            }
            return list;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "citirea prieteniilor");
        }
    }

    /**
     * Returns one page of a user's friends ordered by identifier. A single SELECT joins
     * friendships with users and is paginated in SQL; the total is counted on the same connection.
     * @param userId the identifier of the user whose friends are listed
     * @param pageable the requested page number and size
     * @return the requested page of friends; empty when the user has no friends or the page is past the last one
     * @throws IllegalArgumentException if userId or pageable is null
     * @throws RepositoryException if database query fails
     */
    @Override
    public Page<User> findFriendsOnPage(Long userId, Pageable pageable) {
        if (userId == null || pageable == null) {
            throw new IllegalArgumentException("ID-ul si Pageable nu pot fi null!");
        }
        List<User> friends = new ArrayList<>();
        String pageSql = "SELECT u.id, u.first_name, u.last_name "
                + "FROM friendships f "
                + "JOIN users u ON u.id = CASE WHEN f.id1 = ? THEN f.id2 ELSE f.id1 END "
                + "WHERE f.id1 = ? OR f.id2 = ? "
                + "ORDER BY u.id LIMIT ? OFFSET ?";
        String countSql = "SELECT count(*) AS total FROM friendships WHERE id1 = ? OR id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement pagePs = connection.prepareStatement(pageSql);
             PreparedStatement countPs = connection.prepareStatement(countSql)) {
            pagePs.setLong(1, userId);
            pagePs.setLong(2, userId);
            pagePs.setLong(3, userId);
            pagePs.setInt(4, pageable.getPageSize());
            pagePs.setInt(5, pageable.getPageNumber() * pageable.getPageSize());
            try (ResultSet rs = pagePs.executeQuery()) {
                while (rs.next()) {
                    User friend = new User(rs.getString("first_name"), rs.getString("last_name"));
                    friend.setId(rs.getLong("id"));
                    friends.add(friend);
                }
            }
            countPs.setLong(1, userId);
            countPs.setLong(2, userId);
            int total = 0;
            try (ResultSet rs = countPs.executeQuery()) {
                if (rs.next()) {
                    total = rs.getInt("total");
                }
            }
            return new Page<>(friends, total);
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "citirea paginata a prietenilor");
        }
    }

    /**
     * Inserts a friendship into PostgreSQL.
     * @param entity the friendship to save
     * @return null on insertion, or the entity if the friendship already exists
     * @throws IllegalArgumentException if entity is null
     * @throws domain.validator.ValidationException if friendship validation fails
     * @throws RepositoryException if database insertion fails
     */
    @Override
    public Friendship save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        validator.validate(entity);
        if (findOne(entity.getID()) != null) {
            return entity;
        }
        String sql = "INSERT INTO friendships (id1, id2, friends_from) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, entity.getFirstUserId());
            ps.setLong(2, entity.getSecondUserId());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getFriendsFrom()));
            ps.executeUpdate();
            return null;
        } catch (SQLException e) {
            if ("23505".equals(e.getSQLState())) {
                return entity;
            }
            throw DbExceptionHelper.wrap(e, "salvarea prieteniei");
        }
    }

    /**
     * Removes a friendship by its participant IDs.
     * @param id the pair of user IDs
     * @return the removed friendship, or null if absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if database deletion fails
     */
    @Override
    public Friendship delete(Tuple<Long, Long> id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        Friendship existing = findOne(id);
        if (existing == null) {
            return null;
        }
        Tuple<Long, Long> normalized = Friendship.createID(id.getFirst(), id.getSecond());
        String sql = "DELETE FROM friendships WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, normalized.getFirst());
            ps.setLong(2, normalized.getSecond());
            ps.executeUpdate();
            return existing;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "stergerea prieteniei");
        }
    }

    /**
     * Updates an existing friendship.
     * @param entity the friendship with modified properties
     * @return null on successful update, or entity if the ID was not found
     * @throws IllegalArgumentException if entity or its ID is null
     * @throws domain.validator.ValidationException if validation fails
     * @throws RepositoryException if database update fails
     */
    @Override
    public Friendship update(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        if (entity.getID() == null) {
            throw new IllegalArgumentException("ID-ul prieteniei nu poate fi null!");
        }
        validator.validate(entity);
        String sql = "UPDATE friendships SET friends_from = ? WHERE id1 = ? AND id2 = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setTimestamp(1, Timestamp.valueOf(entity.getFriendsFrom()));
            ps.setLong(2, entity.getFirstUserId());
            ps.setLong(3, entity.getSecondUserId());
            int affected = ps.executeUpdate();
            if (affected == 0) {
                return entity;
            }
            return null;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "actualizarea prieteniei");
        }
    }
}
