public class ComplexNumber {
    private final double real;
    private final double imaginary;

    private String formatter(double d) {
        if(d == (long) d) {
            return String.format("%d", (long) d);
        }
        return String.format("%s", d);
    }

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public String toString() {
        if (real == 0 && imaginary == 0) {
            return "0";
        }
        else if (real == 0) {
            if (imaginary == 1) {
                return "i";
            }
            if (imaginary == -1) {
                return "-i";
            }
            return formatter(imaginary) + " * i";
        }
        else if (imaginary == 0){
            return formatter(real);
        }
        else if (imaginary < 0) {
            return imaginary == - 1 ? formatter(real) + " - i" : formatter(real) + " - " + formatter(-imaginary) + " * i";
        }
        else {
            return imaginary == 1 ? formatter(real) + " + i" : formatter(real) + " + " + formatter(imaginary) + " * i";
        }
    }
}
