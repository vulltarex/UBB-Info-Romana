package repository;

import domain.Entity;
import util.paging.Page;
import util.paging.Pageable;

/**
 * Repository that can return its entities one page at a time.
 * @param <ID> the identifier type
 * @param <E> the entity type
 */
public interface PagingRepository<ID, E extends Entity<ID>> extends Repository<ID, E> {
    /**
     * Returns the entities on the requested page, ordered by identifier.
     * @param pageable the requested page number and size
     * @return the requested page; its element list is empty when the page is past the last one
     * @throws RepositoryException if persistence fails
     */
    Page<E> findAllOnPage(Pageable pageable);
}
