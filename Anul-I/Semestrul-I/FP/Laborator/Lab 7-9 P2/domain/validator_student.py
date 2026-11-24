class ValidationError(Exception):
    pass

class ValidatorStudent:
    @staticmethod
    def validate(student):
        errors = []
        if not isinstance(student.get_nume(), str) or student.get_nume().strip() == "":
            errors.append("Numele studentului nu poate fi vid!")
        if not isinstance(student.get_id(), int) or student.get_id() <= 0:
            errors.append("ID-ul studentului trebuie sa fie strict pozitiv!")
        if not isinstance(student.get_grupa(), int) or student.get_grupa() <= 0:
            errors.append("Grupa studentului trebuie sa fie strict pozitiva!")

        if errors:
           raise ValidationError("\n".join(errors))

