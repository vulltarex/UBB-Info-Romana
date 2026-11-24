public class DivideOperation implements Operation {
    @Override
    public ComplexNumber apply(ComplexNumber a, ComplexNumber b) {
        double resultReal = (a.getReal() * b.getReal() + a.getImaginary() * b.getImaginary())
                / (b.getReal() * b.getReal() + b.getImaginary() * b.getImaginary());
        double resultImaginary = (a.getImaginary() * b.getReal() - a.getReal() * b.getImaginary())
                / (b.getReal() * b.getReal() + b.getImaginary() * b.getImaginary());
        return new ComplexNumber(resultReal, resultImaginary);
    }
}
