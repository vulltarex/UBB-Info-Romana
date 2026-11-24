public class OperationFactory {
    public static Operation create(String symbol) {
        switch (symbol){
            case "+":
                return new AddOperation();
            case "-":
                return new SubtractOperation();
            case "*":
                return new MultiplyOperation();
            case "/":
                return new DivideOperation();
            default:
                return null;
        }
//        return switch (symbol) {
//            case "+" -> new AddOperation();
//            case "-" -> new SubtractOperation();
//            case "*" -> new MultiplyOperation();
//            case "/" -> new DivideOperation();
//            default -> null;
//        };
    }
}
