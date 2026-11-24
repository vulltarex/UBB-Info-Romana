package curs.util;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BinaryOperator;
import java.util.function.Function;

public final class Colectii {
    public Colectii() {}

    public static <E> List<E> catreLista(Iterable<E> elemente) {
        List<E> rezultat = new ArrayList<>();

//        for (E e : elemente) {
//            rezultat.add(e);
//        }

        elemente.forEach(rezultat::add);

        return rezultat;
    }

    public static <T, R> List<R> transforma(Iterable<T> elemente, Function<T, R> f) {
        List<R> rezultat = new ArrayList<>();
        for (T t : elemente) {
            rezultat.add(f.apply(t));
        }
        return rezultat;
    }

    public static <E> E reduce(Iterable<E> elemente, BinaryOperator<E> op) {
        E rezultat = null;
        for (E e : elemente) {
            rezultat = (rezultat==null) // if
                    ? e // atunci
                    : op.apply(rezultat, e); // altfel
        }
        return rezultat;
    }
}
