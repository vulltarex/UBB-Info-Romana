package curs.domain;

import java.util.function.Predicate;

public final class CriteriiUtilizator {
    public CriteriiUtilizator() {}

    public static Predicate<Utilizator> prenumeleIncepeCu(String prefix) {
        return u -> u.getFirstName().startsWith(prefix);
    }

    public static Predicate<Utilizator> areNumele(String nume) {
        return u -> u.getLastName().equals(nume);
    }

    public static Predicate<Utilizator> areCelPutinPrieteni(int n) {
        return u -> u.getFriends().size() >= n;
    }

    public static boolean faraPrieteni(Utilizator u) {
        return u.getFriends().isEmpty();
    }
}
