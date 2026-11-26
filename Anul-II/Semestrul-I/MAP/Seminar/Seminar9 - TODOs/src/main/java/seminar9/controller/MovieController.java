package seminar9.controller;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;
import seminar9.domain.Movie;
import seminar9.service.MovieService;
import seminar9.util.Page;
import seminar9.util.Sort;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class MovieController {
    private static final int PAGE_SIZE = 3;

    @FXML private TableView<Movie> movieTable;
    @FXML private TableColumn<Movie, Long> idColumn;
    @FXML private TableColumn<Movie, String> titleColumn;
    @FXML private TableColumn<Movie, String> directorColumn;
    @FXML private TableColumn<Movie, Integer> yearColumn;
    @FXML private TableColumn<Movie, Integer> durationColumn;
    @FXML private Button previousButton;
    @FXML private Button nextButton;
    @FXML private Label pageLabel;
    @FXML private Button updateButton;
    @FXML private Button deleteButton;
    @FXML private ComboBox<String> sortFieldBox;
    @FXML private ComboBox<String> sortDirectionBox;
    @FXML private TextField searchBar;

    private MovieService service;
    private int pageNumber = 0;
    private int totalPages = 1;

    @FXML
    private void initialize() {
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        titleColumn.setCellValueFactory(new PropertyValueFactory<>("title"));
        directorColumn.setCellValueFactory(new PropertyValueFactory<>("director"));
        yearColumn.setCellValueFactory(new PropertyValueFactory<>("year"));
        durationColumn.setCellValueFactory(new PropertyValueFactory<>("duration"));
        var noSelection = movieTable.getSelectionModel().selectedItemProperty().isNull();
        // TODO 5: bind the disable property of updateButton and deleteButton to noSelection
        //  (the buttons must be disabled while no movie is selected)

        updateButton.disableProperty().bind(noSelection);
        deleteButton.disableProperty().bind(noSelection);

        sortFieldBox.getItems().setAll("id", "title", "director", "year", "duration");
        sortFieldBox.setValue("id");
        sortDirectionBox.getItems().setAll("Ascending", "Descending");
        sortDirectionBox.setValue("Ascending");
        sortDirectionBox.disableProperty().bind(sortFieldBox.valueProperty().isEqualTo("id"));
    }

    @FXML
    private void onSortChanged() {
        if (service == null) return;   // fired while initializing the combo boxes
        // TODO 4: the sort changed, so go back to the first page and reload the table
        pageNumber = 0;
        loadPage();
    }

    private Page<Movie> fetchPage() {
        String field = sortFieldBox.getValue();
        if ("id".equals(field))       // default order (by id) of the repository
            return service.findAllOnPage(pageNumber, PAGE_SIZE);
        return service.findAllOnPage(pageNumber, PAGE_SIZE,
                new Sort(field, "Ascending".equals(sortDirectionBox.getValue())));
    }

    private Page<Movie> fetchPage(String text) {
        String field = sortFieldBox.getValue();
        if ("id".equals(field))       // default order (by id) of the repository
            return service.findAllOnPage(pageNumber, PAGE_SIZE, text);
        return service.findAllOnPage(pageNumber, PAGE_SIZE,
                new Sort(field, "Ascending".equals(sortDirectionBox.getValue())));
    }

    public void setService(MovieService service) {
        this.service = service;
        loadPage();
    }

    @FXML
    private void onPrevious() {
        // TODO 1: go to the previous page (update pageNumber, then reload the table using loadPage())
        if (pageNumber > 0) {
            pageNumber--;
            loadPage();
        }
    }

    @FXML
    private void onNext() {
        // TODO 2: go to the next page (update pageNumber, then reload the table using loadPage())
        if (pageNumber < totalPages - 1) {
            pageNumber++;
            loadPage();
        }
    }

    @FXML
    private void onAdd() {
        openForm(null, "Add movie");
    }

    @FXML
    private void onUpdate() {
        // TODO 6: get the selected movie from movieTable and, if there is one,
        //  open the form with it (see onAdd() and openForm())
        Movie selected = movieTable.getSelectionModel().getSelectedItem();
        openForm(selected, "Edit movie");
    }

    @FXML
    private void onDelete() {
        Movie selected = movieTable.getSelectionModel().getSelectedItem();
        if (selected == null)
            return;
        if (!Alerts.confirm(movieTable, "Delete movie",
                "Delete \"" + selected.getTitle() + "\" (id " + selected.getId() + ")?"))
            return;
        try {
            service.deleteMovie(selected.getId());
        } catch (RuntimeException e) {
            Alerts.error(movieTable, "Delete failed", "Error while deleting: " + e.getMessage());
            return;
        }
        Alerts.info(movieTable, "Movie deleted", "\"" + selected.getTitle() + "\" was deleted.");
        loadPage();
    }

    @FXML
    private void onSearch() {
        loadPage();
    }
    private void openForm(Movie movie, String title) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/seminar9/movie-form-view.fxml"));
            Stage dialog = new Stage();
            dialog.setScene(new Scene(loader.load()));
            MovieFormController controller = loader.getController();
            controller.setService(service, movie);
            Stage owner = (Stage) movieTable.getScene().getWindow();
            dialog.initOwner(owner);
            dialog.initModality(Modality.WINDOW_MODAL);
            dialog.getIcons().setAll(owner.getIcons());
            dialog.setTitle(title);
            dialog.setResizable(false);
            dialog.showAndWait();
            if (controller.isSaved())
                loadPage();
        } catch (IOException e) {
            Alerts.error(movieTable, "Error", "Cannot open the form: " + e.getMessage());
        }
    }

    private void loadPage() {
        try {
            Page<Movie> page;
            if (searchBar.getText().isEmpty()) {
                page = fetchPage();
            }
            else {
                page = fetchPage(searchBar.getText());
            }
            totalPages = Math.max(1, (page.getTotalNumberOfElements() + PAGE_SIZE - 1) / PAGE_SIZE);
            if (pageNumber >= totalPages) {   // e.g. the last movie of the last page was deleted
                pageNumber = totalPages - 1;
                page = fetchPage();
            }
            if (pageNumber == 0) {
                previousButton.setDisable(true);
            }
            else {
                previousButton.setDisable(false);
            }

            if (pageNumber == totalPages - 1) {
                nextButton.setDisable(true);
            }
            else {
                nextButton.setDisable(false);
            }
            List<Movie> movies = new ArrayList<>();
            page.getElementsOnPage().forEach(movies::add);
            movieTable.setItems(FXCollections.observableList(movies));
            pageLabel.setText((pageNumber + 1) + " / " + totalPages);
        } catch (RuntimeException e) {
            Alerts.error(movieTable, "Database error", "Error while loading movies: " + e.getMessage());
        }
        // TODO 3: show "Page x / y" in pageLabel (pageNumber starts at 0),
        //  disable previousButton on the first page and nextButton on the last page
    }
}
