public class MultiplyOperation implements Operation {
    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double resultReal = a.getReal() * b.getReal() - a.getImaginary() * b.getImaginary();
        double resultImaginary = a.getReal() * b.getImaginary() + a.getImaginary() * b.getReal();

        return new ComplexNumber(resultReal, resultImaginary);
    }
}
