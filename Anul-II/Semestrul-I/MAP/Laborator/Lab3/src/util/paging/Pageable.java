package util.paging;

/**
 * Describes which page is requested: its zero-based number and its size.
 */
public class Pageable {
    private final int pageNumber;
    private final int pageSize;

    /**
     * Creates a page request.
     * @param pageNumber the zero-based page number
     * @param pageSize the maximum number of elements on a page
     */
    public Pageable(int pageNumber, int pageSize) {
        this.pageNumber = pageNumber;
        this.pageSize = pageSize;
    }

    /**
     * Returns the requested page number.
     * @return the zero-based page number
     */
    public int getPageNumber() {
        return pageNumber;
    }

    /**
     * Returns the requested page size.
     * @return the maximum number of elements on a page
     */
    public int getPageSize() {
        return pageSize;
    }
}
