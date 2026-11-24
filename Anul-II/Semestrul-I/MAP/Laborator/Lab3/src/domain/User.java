package domain;

/** User with a first name, a last name and a Long identifier. */
public class User extends Entity<Long> {
    private String firstName;
    private String lastName;

    /**
     * Creates a User instance.
     * @param firstName the first name
     * @param lastName the last name
     */
    public User(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /**
     * Returns the first name.
     * @return the first name
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Changes the first name.
     * @param firstName the new first name
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Returns the last name.
     * @return the last name
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Changes the last name.
     * @param lastName the new last name
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }
}
