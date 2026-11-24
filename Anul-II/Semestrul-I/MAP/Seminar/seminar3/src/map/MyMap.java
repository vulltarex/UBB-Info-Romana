package map;

import domain.Student;

import java.util.*;

public class MyMap {
    public static class MedieDescComparator implements Comparator<Integer> {
        @Override
        public int compare(Integer a, Integer b) {
            return Integer.compare(a, b);
        }
    }

    private TreeMap<Integer, List<Student>> map = new TreeMap<>(new MedieDescComparator());

    public void add(Student s) {
        Objects.requireNonNull(s, "Studentul nu poate fi null!");
        float medie = s.getMedia();
        if (!Float.isFinite(medie)) {
            throw new IllegalArgumentException("Valoarea nu poate fi infinita!");
        }
        if (!(medie > 0 && medie <= 10)) {
            throw new IllegalArgumentException("Valoarea trebuie sa fie cuprinsa intre 0 si 10!");
        }
        int medieRotunjita = Math.round(medie);

        map.computeIfAbsent(medieRotunjita, x -> new ArrayList<>()).add(s);
    }

    public Set<Map.Entry<Integer, List<Student>>> getEntries() {
        //return Collections.unmodifiableMap(map).entrySet();
        return map.entrySet();
    }
}
