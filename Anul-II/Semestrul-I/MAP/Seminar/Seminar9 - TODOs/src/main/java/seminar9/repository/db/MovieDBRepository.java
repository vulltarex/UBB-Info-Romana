package seminar9.repository.db;

import seminar9.domain.Movie;
import seminar9.repository.MovieRepository;
import seminar9.repository.RepositoryException;
import seminar9.util.Page;
import seminar9.util.Pageable;
import seminar9.util.Sort;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Optional;

public class MovieDBRepository implements MovieRepository {
    private final String url;
    private final String username;
    private final String password;

    public MovieDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Movie> findOne(Long id) {
        if (id == null)
            throw new IllegalArgumentException("id must not be null");
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement("select * from filme where id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Movie movie = new Movie(resultSet.getString("titlu"),
                            resultSet.getString("regizor"),
                            resultSet.getInt("an"),
                            resultSet.getInt("durata"));
                    movie.setId(id);
                    return Optional.of(movie);
                }
            }

        } catch (SQLException e) {
            throw new RepositoryException("Error while reading data:" + e.getMessage(), e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Movie> findAll() {
        List<Movie> movies = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement("select * from filme order by id");
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Movie m = new Movie(resultSet.getString("titlu"),
                        resultSet.getString("regizor"),
                        resultSet.getInt("an"),
                        resultSet.getInt("durata"));
                m.setId(resultSet.getLong("id"));
                movies.add(m);
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error while reading the movies:" + e.getMessage(), e);
        }
        return movies;
    }

    @Override
    public Optional<Movie> save(Movie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must not be null");
        String sql = "INSERT into filme (titlu, regizor,an, durata) values (?,?,?,?)";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            preparedStatement.setString(1, entity.getTitle());
            preparedStatement.setString(2, entity.getDirector());
            preparedStatement.setInt(3, entity.getYear());
            preparedStatement.setInt(4, entity.getDuration());
            preparedStatement.executeUpdate();
            try (ResultSet resultSet = preparedStatement.getGeneratedKeys()) {
                resultSet.next();
                entity.setId(resultSet.getLong("id"));
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error while saving data:" + e.getMessage(), e);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Movie> delete(Long id) {
        Optional<Movie> found = findOne(id);
        if (found.isEmpty())
            return found;

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement("DELETE FROM filme WHERE id = ?")) {
            ps.setLong(1, id);
            ps.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Error while deleting: " + e.getMessage(), e);
        }
        return found;
    }

    @Override
    public Optional<Movie> update(Movie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must not be null");
        String sql = "UPDATE filme set titlu=?,regizor=?,an=?,durata=? where id=?";

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, entity.getTitle());
            preparedStatement.setString(2, entity.getDirector());
            preparedStatement.setInt(3, entity.getYear());
            preparedStatement.setInt(4, entity.getDuration());
            preparedStatement.setLong(5, entity.getId());
            int nrRows = preparedStatement.executeUpdate();
            return nrRows == 0 ? Optional.of(entity) : Optional.empty();

        } catch (SQLException e) {
            throw new RepositoryException("Error while updating data:" + e.getMessage(), e);
        }
    }

    public List<Movie> findByDirector(String director) {
        List<Movie> movies = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT * FROM filme WHERE regizor = ? ORDER BY an")) {

            statement.setString(1, director);
            try (ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    Movie movie = new Movie(resultSet.getString("titlu"), resultSet.getString("regizor"),
                            resultSet.getInt("an"), resultSet.getInt("durata"));
                    movie.setId(resultSet.getLong("id"));
                    movies.add(movie);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error: " + e.getMessage(), e);
        }
        return movies;
    }

    @Override
    public List<Integer> getYears() {
        List<Integer> years = new ArrayList<>();
        try(Connection connection = DriverManager.getConnection(url, username, password);
        PreparedStatement ps = connection.prepareStatement("select distinct an from filme order by an");
        ResultSet rs = ps.executeQuery()){
            while(rs.next()){
                int year = rs.getInt("an");
                years.add(year);
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error while getting years: " + e.getMessage(), e);
        }
        return years;
    }

    /**
     * Get number of movies
     * @param connection
     * @return
     * @throws SQLException
     */
    private int count(Connection connection) throws SQLException {
        String sql = "select count(*) as count from filme";
        try (PreparedStatement statement = connection.prepareStatement(sql);
             ResultSet result = statement.executeQuery()) {
            int totalNumberOfMovies = 0;
            if (result.next()) {
                totalNumberOfMovies = result.getInt("count");
            }
            return totalNumberOfMovies;
        }
    }

    private List<Movie> findAllOnPage(Connection connection, Pageable pageable) throws SQLException {
        List<Movie> moviesOnPage = new ArrayList<>();
        String sql = "select * from filme order by id limit ? offset ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, pageable.getPageSize());
            statement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            try (ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                   Movie m = new Movie(resultSet.getString("titlu"),
                           resultSet.getString("regizor"),
                           resultSet.getInt("an"),
                           resultSet.getInt("durata"));
                    m.setId(resultSet.getLong("id"));
                    moviesOnPage.add(m);
                }
            }
        }
        return moviesOnPage;
    }

    @Override
    public Page<Movie> findAllOnPage(Pageable pageable) {
        try(Connection connection = DriverManager.getConnection(url, username, password)){
            int totalNumberOfMovies = count(connection);
            List<Movie>moviesOnPage;
            if(totalNumberOfMovies > 0){
                moviesOnPage = findAllOnPage(connection, pageable);
            }else{
                moviesOnPage = new ArrayList<>();
            }
            return new Page<>(moviesOnPage, totalNumberOfMovies);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    // ORDER BY cannot use "?" parameters, so the column name is taken only from this whitelist
    // (never concatenate user input directly into SQL -> SQL injection).
    private static final Map<String, String> SORT_COLUMNS = Map.of(
            "title", "titlu",
            "director", "regizor",
            "year", "an",
            "duration", "durata");

    @Override
    public Page<Movie> findAllOnPage(Pageable pageable, Sort sort) {
        String field = sort.field() == null ? "" : sort.field().trim().toLowerCase();
        String column = SORT_COLUMNS.get(field);
        if (column == null)
            throw new IllegalArgumentException("Cannot sort by: " + sort.field() + ". Allowed: " + SORT_COLUMNS.keySet());

        // id as a second criterion keeps the order stable when values are equal (same year etc.)
        String sql = "select * from filme order by " + column + (sort.ascending() ? " asc" : " desc")
                + ", id limit ? offset ?";
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            int totalNumberOfMovies = count(connection);
            List<Movie> moviesOnPage = new ArrayList<>();
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setInt(1, pageable.getPageSize());
                statement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
                try (ResultSet resultSet = statement.executeQuery()) {
                    while (resultSet.next()) {
                        Movie m = new Movie(resultSet.getString("titlu"),
                                resultSet.getString("regizor"),
                                resultSet.getInt("an"),
                                resultSet.getInt("durata"));
                        m.setId(resultSet.getLong("id"));
                        moviesOnPage.add(m);
                    }
                }
            }
            return new Page<>(moviesOnPage, totalNumberOfMovies);
        } catch (SQLException e) {
            throw new RepositoryException("Sorted pagination failed", e);
        }
    }

    @Override
    public Page<Movie> findAllOnPage(Pageable pageable, String text) {
        String field = text == null ? "" : text.trim().toLowerCase();
        // id as a second criterion keeps the order stable when values are equal (same year etc.)
        String sql = "select titlu, regizor, an, durata from filme where titlu like \"" + text
                + "\", id limit ? offset ?";
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            int totalNumberOfMovies = count(connection);
            List<Movie> moviesOnPage = new ArrayList<>();
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setInt(1, pageable.getPageSize());
                statement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
                try (ResultSet resultSet = statement.executeQuery()) {
                    while (resultSet.next()) {
                        Movie m = new Movie(resultSet.getString("titlu"),
                                resultSet.getString("regizor"),
                                resultSet.getInt("an"),
                                resultSet.getInt("durata"));
                        m.setId(resultSet.getLong("id"));
                        moviesOnPage.add(m);
                    }
                }
            }
            return new Page<>(moviesOnPage, totalNumberOfMovies);
        } catch (SQLException e) {
            throw new RepositoryException("Sorted pagination failed", e);
        }
    }
}
