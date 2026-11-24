package repository;

import domain.Friendship;
import domain.Tuple;
import domain.validator.Validator;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/** Text conversion for friendships: firstUserId;secondUserId;ISO-date. */
public class FriendshipFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Friendship>
        implements FriendshipRepository {
    /**
     * Creates a FriendshipFileRepository instance.
     * @param validator the fully initialized validation strategy
     * @param filename the relative UTF-8 text file path
     * @throws IllegalArgumentException if a parameter is invalid
     * @throws RepositoryException if existing data cannot be loaded
     */
    public FriendshipFileRepository(Validator<Friendship> validator, String filename) {
        super(validator, filename);
    }

    /** {@inheritDoc} */
    @Override
    protected Friendship extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length != 3) throw new IllegalArgumentException("Se asteapta id1;id2;dataPrieteniei!");
        return new Friendship(Long.parseLong(fields[0]), Long.parseLong(fields[1]),
                LocalDateTime.parse(fields[2], DateTimeFormatter.ISO_LOCAL_DATE_TIME));
    }

    /** {@inheritDoc} */
    @Override
    protected String createEntityAsString(Friendship entity) {
        return entity.getFirstUserId() + ";" + entity.getSecondUserId() + ";"
                + entity.getFriendsFrom().format(DateTimeFormatter.ISO_LOCAL_DATE_TIME);
    }
}
