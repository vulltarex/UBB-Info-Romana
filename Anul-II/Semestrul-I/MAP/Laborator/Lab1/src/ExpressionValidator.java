public class ExpressionValidator {
    private final ComplexNumberParser parser;

    public ExpressionValidator(ComplexNumberParser parser) {
        this.parser = parser;
    }

    public boolean isValid(String[] s) {
        if(s.length % 2 == 0 || s.length < 3) return false;
        if(!s[1].matches("[+/*-]")) return false;

        for (int i = 0; i < s.length; i++) {
            if(i % 2 == 0 && !parser.isValid(s[i])) {
                return false;
            } else if(i % 2 == 1 && !s[i].equals(s[1])) {
                return false;
            }
        }
        return true;
    }
}
