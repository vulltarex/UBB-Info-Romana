import javax.swing.*;

public class StandardComplexParser implements ComplexNumberParser {
    @Override
    public boolean isValid(String s) {
        if (s == null) return false;
        s = s.replaceAll("\\s+", "");
        if(s.matches("[+-]?0*(\\.0+)?[+-]0*(\\.0+)?\\*i")) return false;
        return s.matches("[+-]?[0-9]+(\\.[0-9]+)?[+-]([0-9]+(\\.[0-9]+)?\\*)?i");
    }

    @Override
    public ComplexNumber parse(String s) {
        s = s.replaceAll("\\s+", "");
        int separator = -1;
        for (int i = 1; i < s.length(); i++) {
            if(s.charAt(i) == '+' || s.charAt(i) == '-') {
                separator = i;
                break;
            }
        }
        String real, imaginary;

        real = s.substring(0, separator);
        imaginary = s.substring(separator);
        imaginary = imaginary.replaceAll("[*i]", "");

        if(imaginary.length() == 1) {
            imaginary = imaginary + "1";
        }

        double realDouble = Double.parseDouble(real);
        double imaginaryDouble = Double.parseDouble(imaginary);

        return new ComplexNumber(realDouble, imaginaryDouble);
    }
}