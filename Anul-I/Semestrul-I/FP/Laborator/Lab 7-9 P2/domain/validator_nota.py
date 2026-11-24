class ValidationError(Exception):
    pass

class ValidatorNota:
    @staticmethod
    def validate(nota):
        errors = []
        if not isinstance(nota.get_val_nota(), int) or nota.get_val_nota() < 1 or nota.get_val_nota() > 10:
            errors.append("Nota invalida!")
        if errors:
            raise ValidationError("\n".join(errors))