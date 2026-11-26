package seminar9.repository;

import seminar9.domain.Movie;
import java.util.List;

public interface MovieRepository extends PagingRepository<Long, Movie> {
    List<Integer> getYears();
}
