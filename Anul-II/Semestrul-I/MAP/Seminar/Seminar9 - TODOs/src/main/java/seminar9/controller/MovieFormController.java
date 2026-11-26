package seminar9.controller;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import seminar9.domain.Movie;
import seminar9.domain.validators.ValidationException;
import seminar9.service.MovieService;

/**
 * Form used both for adding (movie == null) and updating a movie.
 * The id is never editable: it is generated on add and kept on update.
 */
public class MovieFormController {
    @FXML private TextField titleField;
    @FXML private TextField directorField;
    @FXML private TextField yearField;
    @FXML private TextField durationField;

    private MovieService service;
    private Movie movie;          // null = add mode
    private boolean saved = false;

    public void setService(MovieService service, Movie movie) {
        this.service = service;
        this.movie = movie;
        if (movie != null) {
            titleField.setText(movie.getTitle());
            directorField.setText(movie.getDirector());
            yearField.setText(String.valueOf(movie.getYear()));
            durationField.setText(String.valueOf(movie.getDuration()));
            // TODO 7: edit mode - fill titleField, directorField, yearField and durationField
            //  with the data of the movie (hint: String.valueOf for numbers)
        }
    }

    public boolean isSaved() {
        return saved;
    }

    @FXML
    private void onSave() {
        int year, duration;
        try {
            year = Integer.parseInt(yearField.getText().trim());
            duration = Integer.parseInt(durationField.getText().trim());
        } catch (NumberFormatException e) {
            showAlert(Alert.AlertType.ERROR, "Invalid movie", "Year and duration must be numbers.");
            return;
        }
        String title = titleField.getText().trim();
        String director = directorField.getText().trim();
        Movie result;
        try {
            result = movie == null
                    ? service.addMovie(title, director, year, duration)
                    : service.updateMovie(movie.getId(), title, director, year, duration);
        } catch (ValidationException e) {
            showAlert(Alert.AlertType.ERROR, "Invalid movie", String.join("\n", e.getMessage().split(";")));
            return;
        } catch (RuntimeException e) {
            showAlert(Alert.AlertType.ERROR, "Save failed", "Error while saving the movie: " + e.getMessage());
            return;
        }
        saved = true;
        showAlert(Alert.AlertType.INFORMATION, movie == null ? "Movie saved" : "Movie updated",
                "\"" + result.getTitle() + "\" was " + (movie == null ? "saved" : "updated")
                        + " (id " + result.getId() + ").");
        close();
    }

    @FXML
    private void onCancel() {
        close();
    }

    private void close() {
        ((Stage) titleField.getScene().getWindow()).close();
    }

    private void showAlert(Alert.AlertType type, String header, String message) {
        Alerts.show(titleField, type, header, message);
    }
}
