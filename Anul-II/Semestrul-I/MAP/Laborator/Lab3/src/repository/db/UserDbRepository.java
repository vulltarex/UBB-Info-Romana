package repository.db;

import domain.User;
import domain.validator.Validator;
import repository.PagingRepository;
import repository.RepositoryException;
import repository.UserRepository;
import util.paging.Page;
import util.paging.Pageable;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 * JDBC persistence for users in PostgreSQL.
 */
public class UserDbRepository implements UserRepository, PagingRepository<Long, User> {
    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates a UserDbRepository instance.
     * @param validator the validation strategy for users
     * @param url the configured connection URL
     * @param user the configured database user
     * @param password the configured database password
     * @throws IllegalArgumentException if a dependency is null
     */
    public UserDbRepository(Validator<User> validator, String url, String user, String password) {
        if (validator == null || url == null || user == null || password == null) {
            throw new IllegalArgumentException("Parametrii repository-ului DB nu pot fi null!");
        }
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * Finds a user by identifier.
     * @param id the user ID
     * @return the user found, or null if absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if database lookup fails
     */
    @Override
    public User findOne(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        String sql = "SELECT id, first_name, last_name FROM users WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    User entity = new User(rs.getString("first_name"), rs.getString("last_name"));
                    entity.setId(rs.getLong("id"));
                    return entity;
                }
                return null;
            }
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "cautarea utilizatorului");
        }
    }

    /**
     * Returns all stored users.
     * @return list of all users
     * @throws RepositoryException if database query fails
     */
    @Override
    public Iterable<User> findAll() {
        List<User> users = new ArrayList<>();
        String sql = "SELECT id, first_name, last_name FROM users";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                User userEntity = new User(rs.getString("first_name"), rs.getString("last_name"));
                userEntity.setId(rs.getLong("id"));
                users.add(userEntity);
            }
            return users;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "citirea utilizatorilor");
        }
    }

    /**
     * Returns one page of users ordered by identifier. The page query and the count query
     * run on the same connection, so the page and the total describe the same data.
     * @param pageable the requested page number and size
     * @return the requested page; empty when the page is past the last one
     * @throws IllegalArgumentException if pageable is null
     * @throws RepositoryException if database query fails
     */
    @Override
    public Page<User> findAllOnPage(Pageable pageable) {
        if (pageable == null) {
            throw new IllegalArgumentException("Pageable nu poate fi null!");
        }
        List<User> users = new ArrayList<>();
        String pageSql = "SELECT id, first_name, last_name FROM users ORDER BY id LIMIT ? OFFSET ?";
        String countSql = "SELECT count(*) AS total FROM users";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement pagePs = connection.prepareStatement(pageSql);
             PreparedStatement countPs = connection.prepareStatement(countSql)) {
            pagePs.setInt(1, pageable.getPageSize());
            pagePs.setInt(2, pageable.getPageNumber() * pageable.getPageSize());
            try (ResultSet rs = pagePs.executeQuery()) {
                while (rs.next()) {
                    User userEntity = new User(rs.getString("first_name"), rs.getString("last_name"));
                    userEntity.setId(rs.getLong("id"));
                    users.add(userEntity);
                }
            }
            int total = 0;
            try (ResultSet rs = countPs.executeQuery()) {
                if (rs.next()) {
                    total = rs.getInt("total");
                }
            }
            return new Page<>(users, total);
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "citirea paginata a utilizatorilor");
        }
    }

    /**
     * Inserts a user into PostgreSQL, obtaining the generated identifier.
     * @param entity the user to save
     * @return null on insertion, or the entity if insertion failed
     * @throws IllegalArgumentException if entity is null
     * @throws domain.validator.ValidationException if user validation fails
     * @throws RepositoryException if database insertion fails
     */
    @Override
    public User save(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        validator.validate(entity);
        String sql = "INSERT INTO users (first_name, last_name) VALUES (?, ?)";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.executeUpdate();
            try (ResultSet rs = ps.getGeneratedKeys()) {
                if (rs.next()) {
                    entity.setId(rs.getLong(1));
                }
            }
            return null;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "salvarea utilizatorului");
        }
    }

    /**
     * Removes a user by identifier.
     * @param id the identifier of the user to delete
     * @return the removed user, or null if absent
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if database deletion fails
     */
    @Override
    public User delete(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("ID-ul nu poate fi null!");
        }
        User existing = findOne(id);
        if (existing == null) {
            return null;
        }
        String sql = "DELETE FROM users WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, id);
            ps.executeUpdate();
            return existing;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "stergerea utilizatorului");
        }
    }

    /**
     * Updates an existing user.
     * @param entity the user with modified properties
     * @return null on successful update, or entity if the ID was not found
     * @throws IllegalArgumentException if entity or its ID is null
     * @throws domain.validator.ValidationException if validation fails
     * @throws RepositoryException if database update fails
     */
    @Override
    public User update(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null!");
        }
        if (entity.getID() == null) {
            throw new IllegalArgumentException("ID-ul utilizatorului nu poate fi null!");
        }
        validator.validate(entity);
        String sql = "UPDATE users SET first_name = ?, last_name = ? WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setLong(3, entity.getID());
            int affected = ps.executeUpdate();
            if (affected == 0) {
                return entity;
            }
            return null;
        } catch (SQLException e) {
            throw DbExceptionHelper.wrap(e, "actualizarea utilizatorului");
        }
    }
}
