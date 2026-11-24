package repository.db;

import repository.RepositoryException;

import java.sql.SQLException;

/**
 * Helper class that translates SQLExceptions into user-facing RepositoryExceptions.
 */
public final class DbExceptionHelper {
    private DbExceptionHelper() {}

    /**
     * Translates a SQLException into a specific RepositoryException.
     * @param e the underlying SQL exception
     * @param operation the description of the attempted database operation
     * @return a RepositoryException with details
     */
    public static RepositoryException wrap(SQLException e, String operation) {
        String details = " [SQLState=" + e.getSQLState() + ", Error=" + e.getMessage() + "]";
        String sqlState = e.getSQLState();
        if (sqlState != null) {
            if (sqlState.startsWith("08")) {
                return new RepositoryException("Serverul bazei de date este oprit sau inaccesibil." + details, e);
            }
            if (sqlState.startsWith("23")) {
                return new RepositoryException("Constrangere de integritate incalcata in baza de date (date duplicate sau invalide)." + details, e);
            }
            if (sqlState.startsWith("28")) {
                return new RepositoryException("Autentificarea la baza de date a esuat (utilizator sau parola incorecta)." + details, e);
            }
        }
        return new RepositoryException("Eroare la " + operation + " in baza de date: " + details, e);
    }
}
