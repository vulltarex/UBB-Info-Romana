import ui.ConsoleUI;

/** Application entry point; no concrete persistence dependencies are selected here. */
public class Main {
    /** Creates the entry point. */
    public Main() {}

    /**
     * Starts the application.
     * @param args unused command-line arguments
     */
    public static void main(String[] args) {
        ConsoleUI.start();
    }
}