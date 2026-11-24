package seminar7.repository.db;

import seminar7.domain.Movie;
import seminar7.domain.validators.Validator;
import seminar7.repository.Repository;
import seminar7.repository.RepositoryException;

import javax.swing.text.html.Option;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MovieDBRepository implements Repository<Long,Movie> {
    private final Validator<Movie> validator;
    private final String url;
    private final String username;
    private final String password;

    public MovieDBRepository(Validator<Movie> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    private Movie fromRow(ResultSet row) throws SQLException {
        Movie movie = new Movie(row.getString("titlu"), row.getString("regizor"),
                row.getInt("an"), row.getInt("durata"));
        movie.setId(row.getLong("id"));

        return movie;
    }

    @Override
    public Optional<Movie> findOne(Long id) {
        if (id == null)
            throw new IllegalArgumentException("Id nu poate fi null");
        String sql = "SELECT id, titlu, regizor, an, durata FROM Filme WHERE ID = ?";
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setLong(1, id);
            ResultSet resSet = statement.executeQuery();
            return resSet.next()
                    ? Optional.of(fromRow(resSet))
                    : Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la cautarea filmului: " + id, e.getCause());
        }
    }

    @Override
    public Iterable<Movie> findAll() {
        List<Movie> movies = new ArrayList<>();
        String sql = "SELECT id, titlu, regizor, an, durata FROM Filme ORDER BY id";
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resSet = statement.executeQuery();
            while (resSet.next()) {
                movies.add(fromRow(resSet));
            }
            return movies;
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la citirea filmelor", e.getCause());
        }
    }

    @Override
    public Optional<Movie> save(Movie entity) {
        if(entity == null) {
            throw new IllegalArgumentException("Entity nu poate fi null");
        }
        if(entity.getId() != null) {
            throw new IllegalArgumentException("Filmul nu opate avea ID");
        }
        String sql = "INSERT INTO Filme(titlu, regizor, an, durata) VALUES (?,?,?,?)";
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement(sql);

            statement.setString(1, entity.getTitle());
            statement.setString(2, entity.getDirector());
            statement.setInt(3, entity.getYear());
            statement.setInt(4, entity.getDuration());

            statement.executeUpdate();
            // pt insert/delete/update returneaza numarul de randuri modificate

            ResultSet resSet = statement.getGeneratedKeys();
            if(!resSet.next()) {
                throw new RepositoryException("Nu s-a generat niciun ID", new SQLException("Lipseste cheia generata"));
            }
            else {
                entity.setId(resSet.getLong(1));
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la salvarea filmului", e.getCause());
        }
    }

    @Override
    public Optional<Movie> delete(Long id) {
        return Optional.empty();
    }

    @Override
    public Optional<Movie> update(Movie entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity nu poate fi null");
        }
        validator.validate(entity);
        if (entity.getId() == null) {
            throw new IllegalArgumentException("ID nu poate fi null");
        }
        String sql = "UPDATE Filme SET titlu = ?, regizor = ?, an = ?, durata = ? WHERE id = ?";
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, entity.getTitle());
            statement.setString(2, entity.getDirector());
            statement.setInt(3, entity.getYear());
            statement.setInt(4, entity.getDuration());
            statement.setLong(5, entity.getId());

            return statement.executeUpdate() == 0
                    ? Optional.of(entity)
                    : Optional.empty();
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la modificarea filmului", e);
        }
    }


    public List<Movie> findByDirector(String director) {
        List<Movie> movies = new ArrayList<>();
        // TODO: Implement the logic to retrieve movies by director order by year from the database
        return movies;
    }
}
