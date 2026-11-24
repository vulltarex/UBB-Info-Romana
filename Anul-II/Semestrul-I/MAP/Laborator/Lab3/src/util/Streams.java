package util;

import java.util.stream.Stream;
import java.util.stream.StreamSupport;

/** Adapts iterable results to sequential streams. */
public final class Streams {
    private Streams() {
    }

    /**
     * Creates a fresh sequential stream in the iterable's encounter order.
     * @param elements the source elements
     * @param <T> the element type
     * @return a stream over the supplied elements
     * @throws NullPointerException if the source is null
     */
    public static <T> Stream<T> stream(Iterable<T> elements) {
        return StreamSupport.stream(elements.spliterator(), false);
    }
}
