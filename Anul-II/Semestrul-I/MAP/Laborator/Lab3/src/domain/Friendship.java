package domain;

import java.time.LocalDateTime;
import java.util.Objects;

/** Undirected friendship identified by its sorted pair of user IDs. */
public class Friendship extends Entity<Tuple<Long, Long>> {
    private LocalDateTime friendsFrom;

    /**
     * Creates a Friendship instance.
     * @param firstId the first user ID
     * @param secondId the second user ID
     * @param friendsFrom the friendship date and time
     * @throws IllegalArgumentException if either ID is null
     */
    public Friendship(Long firstId, Long secondId, LocalDateTime friendsFrom) {
        super(createID(firstId, secondId));
        this.friendsFrom = friendsFrom;
    }

    /**
     * Builds a undirected friendship identifier.
     * @param firstId the first user ID
     * @param secondId the second user ID
     * @return the pair with the smaller ID first
     * @throws IllegalArgumentException if either ID is null
     */
    public static Tuple<Long, Long> createID(Long firstId, Long secondId) {
        if (firstId == null || secondId == null) throw new IllegalArgumentException("ID-urile nu pot fi null!");
        if (firstId <= secondId) return new Tuple<>(firstId, secondId);
        return new Tuple<>(secondId, firstId);
    }

    /**
     * Assigns the entity identifier.
     * @param id the new pair, normalized before assignment
     * @throws IllegalArgumentException if the pair or either element is null
     */
    @Override
    public void setId(Tuple<Long, Long> id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null!");
        super.setId(createID(id.getFirst(), id.getSecond()));
    }

    /**
     * Returns the first participant ID.
     * @return the smaller participant ID
     */
    public Long getFirstUserId() {
        return getID().getFirst();
    }

    /**
     * Returns the second participant ID.
     * @return the larger participant ID
     */
    public Long getSecondUserId() {
        return getID().getSecond();
    }

    /**
     * Checks whether the given user is either participant in this friendship.
     * @param userId the identifier to look for
     * @return whether either participant has that identifier
     */
    public boolean involves(Long userId) {
        return Objects.equals(userId, getFirstUserId()) || Objects.equals(userId, getSecondUserId());
    }

    /**
     * Returns the friendship date and time.
     * @return the date and time when the friendship started
     */
    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    /**
     * Changes the friendship date and time.
     * @param friendsFrom the new friendship date and time
     */
    public void setFriendsFrom(LocalDateTime friendsFrom) {
        this.friendsFrom = friendsFrom;
    }
}
