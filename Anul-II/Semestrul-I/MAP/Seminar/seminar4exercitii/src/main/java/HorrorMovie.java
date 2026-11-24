public class HorrorMovie extends Movie {
    private final int intensityFear;

    public HorrorMovie(String name, int year, int intensityFear) {
        super(name, year);
        this.intensityFear = intensityFear;
    }

    @Override
    public String toString() {
        return super.toString() + ", Intensity fear: " + intensityFear;
    }
}
