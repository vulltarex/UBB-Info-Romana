package domain;

public class StudentValidator implements Validator<Student> {
    @Override
    public void validate(Student s) {
        if (s.getNume() == "") throw new ValidationException("Numele nu poate fi vid");
    }
}
