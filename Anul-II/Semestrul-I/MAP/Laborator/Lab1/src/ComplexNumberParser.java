public interface ComplexNumberParser {
    boolean isValid(String s);
    ComplexNumber parse(String s);
}
