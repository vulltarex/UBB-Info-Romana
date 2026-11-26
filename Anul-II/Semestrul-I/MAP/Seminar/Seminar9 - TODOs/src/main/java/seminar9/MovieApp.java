package seminar9;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import seminar9.controller.MovieController;
import seminar9.domain.Movie;
import seminar9.domain.validators.MovieValidator;
import seminar9.repository.PagingRepository;
import seminar9.repository.Repository;
import seminar9.repository.factory.RepositoryFactory;
import seminar9.service.MovieService;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class MovieApp extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader loader = new FXMLLoader(MovieApp.class.getResource("movie-view.fxml"));
        stage.setScene(new Scene(loader.load()));
        MovieController controller = loader.getController();
        controller.setService(new MovieService(createRepository(), new MovieValidator()));
        stage.setTitle("Cinema");
        stage.getIcons().add(new Image(MovieApp.class.getResourceAsStream("cinema-logo.png")));
        stage.show();
    }

    private static PagingRepository<Long, Movie> createRepository() throws IOException {
        Properties props = new Properties();
        try (InputStream in = MovieApp.class.getResourceAsStream("/config.properties")) {
            props.load(in);
        }
        Repository<Long, Movie> repo = new RepositoryFactory(props).createMovieRepository();
        if (!(repo instanceof PagingRepository<Long, Movie> pagingRepo))
            throw new IllegalStateException("Pagination requires repository.type=DATABASE");
        return pagingRepo;
    }
}
