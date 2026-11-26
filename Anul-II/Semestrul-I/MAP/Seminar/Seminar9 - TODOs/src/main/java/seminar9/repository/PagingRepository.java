package seminar9.repository;

import seminar9.domain.Entity;
import seminar9.util.Page;
import seminar9.util.Pageable;
import seminar9.util.Sort;

public interface PagingRepository<ID , E extends Entity<ID>> extends Repository<ID, E> {

    Page<E> findAllOnPage(Pageable pageable);

    Page<E> findAllOnPage(Pageable pageable, Sort sort);

    Page<E> findAllOnPage(Pageable pageable, String text);
}
