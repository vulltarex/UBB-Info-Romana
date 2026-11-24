import unittest
from domain.problema import ProblemaLaborator
from domain.student import Student
from domain.validator_student import ValidatorStudent, ValidationError as ValidationErrorStudent
from domain.validator_problema import ValidatorProblemaLaborator, ValidationError as ValidationErrorProblema

class TestValidator(unittest.TestCase):
    def setUp(self):
        self.val_student = ValidatorStudent()
        self.val_problema = ValidatorProblemaLaborator()

    def test_validator_blackbox(self):
        s = Student(1, "Cristi", 212)
        try:
            self.val_student.validate(s)
        except ValidationErrorStudent:
            self.fail()
        s = Student(1, "", 212)
        try:
            self.val_student.validate(s)
            self.fail()
        except ValidationErrorStudent:
            pass

    def test_validator_student(self):
        s = Student(-3, "Cristi", 212)
        with self.assertRaises(ValidationErrorStudent):
            self.val_student.validate(s)

        s = Student("a", "Cristi", 212)
        with self.assertRaises(ValidationErrorStudent):
             self.val_student.validate(s)

        s = Student(1, "", 212)
        with self.assertRaises(ValidationErrorStudent):
            self.val_student.validate(s)

        s = Student(1, 3, 212)
        with self.assertRaises(ValidationErrorStudent):
             self.val_student.validate(s)

        s = Student(1, "Cristi", "a")
        with self.assertRaises(ValidationErrorStudent):
             self.val_student.validate(s)

        s = Student(1, "Cristi", -212)
        with self.assertRaises(ValidationErrorStudent):
            self.val_student.validate(s)

    def test_validator_problema(self):
        p = ProblemaLaborator((1, "a"), "Rezolvati", 12)
        with self.assertRaises(ValidationErrorProblema):
             self.val_problema.validate(p)

        p = ProblemaLaborator((1, 1), "", 12)
        with self.assertRaises(ValidationErrorProblema):
            self.val_problema.validate(p)

        p = ProblemaLaborator((1, 1), "Rezolvati", "a")
        with self.assertRaises(ValidationErrorProblema):
             self.val_problema.validate(p)

        p = ProblemaLaborator((1, 1), "Rezolvati", -12)
        with self.assertRaises(ValidationErrorProblema):
            self.val_problema.validate(p)