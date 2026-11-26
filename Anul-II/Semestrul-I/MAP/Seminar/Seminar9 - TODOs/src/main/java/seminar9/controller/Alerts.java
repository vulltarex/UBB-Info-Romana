package seminar9.controller;

import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.stage.Stage;
import javafx.stage.Window;

import java.util.Optional;

/** Themed alerts, owned by the window of the given node. */
final class Alerts {
    private Alerts() {}

    static Optional<ButtonType> show(Node owner, Alert.AlertType type, String header, String message, ButtonType... buttons) {
        Alert alert = new Alert(type, message, buttons);
        alert.setHeaderText(header);
        alert.getDialogPane().getStylesheets().add(Alerts.class.getResource("/seminar9/style.css").toExternalForm());
        Window window = owner.getScene() == null ? null : owner.getScene().getWindow();
        if (window != null) {
            alert.initOwner(window);
            if (window instanceof Stage stage)
                ((Stage) alert.getDialogPane().getScene().getWindow()).getIcons().setAll(stage.getIcons());
        }
        return alert.showAndWait();
    }

    static void error(Node owner, String header, String message) {
        show(owner, Alert.AlertType.ERROR, header, message);
    }

    static void info(Node owner, String header, String message) {
        show(owner, Alert.AlertType.INFORMATION, header, message);
    }

    static boolean confirm(Node owner, String header, String message) {
        return show(owner, Alert.AlertType.CONFIRMATION, header, message, ButtonType.YES, ButtonType.NO)
                .orElse(ButtonType.NO) == ButtonType.YES;
    }
}
