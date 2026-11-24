public class ExpressionEvaluator {
    private final ComplexNumberParser parser;
    private final Operation operation;

    public ExpressionEvaluator(ComplexNumberParser parser, Operation operation) {
        this.parser = parser;
        this.operation = operation;
    }

    public ComplexNumber evaluate(String[] args) {
        ComplexNumber result, operand;
        result = parser.parse(args[0]);
        for (int i = 2; i < args.length; i += 2) {
            operand = parser.parse(args[i]);
            result = operation.apply(result, operand);
        }
        return result;
    }
}
