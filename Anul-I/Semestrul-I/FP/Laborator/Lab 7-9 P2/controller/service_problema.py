import random
import string

from domain.problema import ProblemaLaborator
from domain.validator_problema import *
from repository.repo_problema import DuplicateError

class ProblemaLaboratorService:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add(self, numar_lab, nr_prob, descriere, deadline):
        nr_lab_nr_prob = (numar_lab, nr_prob)
        problema_laborator = ProblemaLaborator(nr_lab_nr_prob, descriere, deadline)
        self.__validator.validate(problema_laborator)
        self.__repo.add(problema_laborator)

    def remove(self, numar_lab_nr_prob):
        self.__repo.remove(numar_lab_nr_prob)

    def update(self, numar_lab_nr_prob, descriere, deadline):
        problema_laborator = ProblemaLaborator(numar_lab_nr_prob, descriere, deadline)
        self.__validator.validate(problema_laborator)
        self.__repo.update(problema_laborator)

    def find_by_numar_lab_nr_prob(self, numar_lab_nr_prob):
        return self.__repo.find_by_numar_lab_nr_prob(numar_lab_nr_prob)

    def get_all(self):
        return self.__repo.get_all()

    def add_random_probleme(self, numar_probleme):
        if numar_probleme == 0:
            return
        characters = string.ascii_lowercase
        nr_lab_nr_prob = (random.randint(1, 14), random.randint(1, 20))
        descriere = ''.join(random.choices(characters, k=15))
        deadline = random.randint(1, 14)
        problema_laborator = ProblemaLaborator(nr_lab_nr_prob, descriere, deadline)
        try:
            self.__validator.validate(problema_laborator)
            self.__repo.add(problema_laborator)
            self.add_random_probleme(numar_probleme - 1)
        except (ValidationError, DuplicateError):
            self.add_random_probleme(numar_probleme)

    # def add_random_probleme(self, numar_probleme):
    #     characters = string.ascii_lowercase
    #     for i in range(numar_probleme):
    #         nr_lab_nr_prob = (random.randint(1, 14), random.randint(1, 20))
    #         descriere = ''.join(random.choices(characters, k = 15))
    #         deadline = random.randint(1, 14)
    #         problema_laborator = ProblemaLaborator(nr_lab_nr_prob, descriere, deadline)
    #         try:
    #             self.__validator.validate(problema_laborator)
    #             self.__repo.add(problema_laborator)
    #         except ValidationError:
    #             i -= 1