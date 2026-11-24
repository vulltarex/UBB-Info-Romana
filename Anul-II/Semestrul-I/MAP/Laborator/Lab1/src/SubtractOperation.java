public class SubtractOperation implements Operation{
    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double resultReal = a.getReal() - b.getReal();
        double resultImaginary = a.getImaginary() - b.getImaginary();

        return new ComplexNumber(resultReal, resultImaginary);
    }
}
