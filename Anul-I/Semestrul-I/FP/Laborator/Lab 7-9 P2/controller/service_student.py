import random
import string

from domain.student import Student
from domain.validator_student import *
from repository.repo_student import DuplicateError


class StudentService:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add(self, id_student, nume, grupa):
        student = Student(id_student, nume, grupa)
        self.__validator.validate(student)
        self.__repo.add(student)

    def remove(self, id_student):
        self.__repo.remove(id_student)

    def update(self, id_student, nume, grupa):
        student = Student(id_student, nume, grupa)
        self.__validator.validate(student)
        self.__repo.update(student)

    def find_by_id(self, id_student):
        return self.__repo.find_by_id(id_student)

    def get_all(self):
        return self.__repo.get_all()

    def add_random_students(self, numar_studenti):
        if numar_studenti == 0:
            return

        characters = string.ascii_lowercase
        nume = ''.join(random.choices(characters, k = 6))
        id_student = random.randint(1, 999)
        grupa = random.randint(1, 500)
        student = Student(id_student, nume, grupa)
        try:
            self.__validator.validate(student)
            self.__repo.add(student)
            self.add_random_students(numar_studenti - 1)
        except (ValidationError, DuplicateError):
            self.add_random_students(numar_studenti)

    # def add_random_students(self, numar_studenti):
    #     characters = string.ascii_lowercase
    #     for i in range(numar_studenti):
    #         nume = ''.join(random.choices(characters, k = 6))
    #         id_student = random.randint(1, 999)
    #         grupa = random.randint(1, 500)
    #         student = Student(id_student, nume, grupa)
    #         try:
    #             self.__validator.validate(student)
    #             self.__repo.add(student)
    #         except ValidationError:
    #             i -= 1