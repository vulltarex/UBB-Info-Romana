public class ActionMovie extends Movie {
    private final boolean isThriller;

    public ActionMovie(String name, int year, boolean isThriller) {
        super(name, year);
        this.isThriller = isThriller;
    }

    @Override
    public String toString() {
        return super.toString() + ", is thriller: " + isThriller;
    }
}
