import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Movie> list = new ArrayList<>();
        list.add(new Movie("Shrek", 2001));
        list.add(new HorrorMovie("The shining", 1986, 8));
        list.add(new HorrorMovie("IT", 2017, 9));
        list.add(new ActionMovie("Star Wars", 1977, false));

        for(Movie movie : list) {
            if(movie instanceof HorrorMovie) {
                System.out.println(movie);
                HorrorMovie horrorMovie = (HorrorMovie) movie;
                System.out.println(horrorMovie);
            }
        }

        try {
            System.out.println("salut");
        }
        finally {
            System.out.println("pa");
        }

        try {
            Integer.parseInt("abcd");
        } catch (NumberFormatException e) {
            System.out.println("Format incorect " + e.getClass().getSimpleName());
        }
        try {
            int x = 1 / 0;
            System.out.println(x);
        }
        catch (ArithmeticException e) {
            System.out.println("Eroare " + e.getClass().getSimpleName());
        }
        try{
            readLines(Path.of("data", "/date.txt"));
        } catch (IOException e) {
            System.out.println("Eroare");
        }
    }
    static void readLines(Path path) throws IOException {
        List<String> lines = Files.readAllLines(path, StandardCharsets.UTF_8);
        for (String line : lines) {
            if(line.contains("test")) {
                System.out.println(line);
            }
        }
    }
}
