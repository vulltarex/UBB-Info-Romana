package util.paging;

/**
 * One page of results together with the total number of elements in the whole collection.
 * @param <E> the element type
 */
public class Page<E> {
    private final Iterable<E> elementsOnPage;
    private final int totalNumberOfElements;

    /**
     * Creates a page.
     * @param elementsOnPage the elements on this page; empty when the page is past the last one
     * @param totalNumberOfElements the number of elements across all pages
     */
    public Page(Iterable<E> elementsOnPage, int totalNumberOfElements) {
        this.elementsOnPage = elementsOnPage;
        this.totalNumberOfElements = totalNumberOfElements;
    }

    /**
     * Returns the elements on this page.
     * @return the elements on this page
     */
    public Iterable<E> getElementsOnPage() {
        return elementsOnPage;
    }

    /**
     * Returns the total number of elements across all pages.
     * @return the total number of elements
     */
    public int getTotalNumberOfElements() {
        return totalNumberOfElements;
    }
}
