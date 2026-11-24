class ValidationError(Exception):
    pass

class ValidatorProblemaLaborator:
    @staticmethod
    def validate(problema_laborator):
        errors = []
        if not isinstance(problema_laborator.get_numar_lab_nr_prob()[0], int) or problema_laborator.get_numar_lab_nr_prob()[0] < 1:
            errors.append("Numar laborator invalid!")
        if not isinstance(problema_laborator.get_numar_lab_nr_prob()[1], int) or problema_laborator.get_numar_lab_nr_prob()[1] < 1:
            errors.append("Numar problema invalid!")
        if not isinstance(problema_laborator.get_descriere(), str) or problema_laborator.get_descriere().strip() == "":
            errors.append("Descrierea problemei nu poate fi vida!")
        if not isinstance(problema_laborator.get_deadline(), int) or problema_laborator.get_deadline() <= 0 or problema_laborator.get_deadline() > 14:
            errors.append("Deadline invalid!")

        if errors:
            raise ValidationError("\n".join(errors))