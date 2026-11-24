public class Main {
    public static void main(String[] args) {
        ComplexNumberParser parser = new StandardComplexParser();
        ExpressionValidator validator = new ExpressionValidator(parser);
        if (args.length == 0) {
            System.out.println("Example usage: java -cp out Main \"2+3*i\" \"+\" \"5-6*i\" \"+\" \"-2+i\"");
        } else if (!validator.isValid(args)) {
            System.out.println("Expresie incorecta!");
        } else {
            Operation operation = OperationFactory.create(args[1]);
            ExpressionEvaluator evaluator = new ExpressionEvaluator(parser, operation);
            ComplexNumber result = evaluator.evaluate(args);
            System.out.println(result);
        }
    }
}