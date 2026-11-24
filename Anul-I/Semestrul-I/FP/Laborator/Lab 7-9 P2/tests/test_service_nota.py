import unittest
from controller.service_nota import ServiceNota
from repository.repo_nota import RepoNota
from repository.repo_student import StudentRepository
from repository.repo_problema import ProblemaLaboratorRepository
from domain.validator_nota import ValidatorNota
from domain.student import Student
from domain.problema import ProblemaLaborator
from utils.sortari import Sortari


class TestServiceNota(unittest.TestCase):
    def setUp(self):
        repo_n = RepoNota()
        val_n = ValidatorNota()
        repo_s = StudentRepository()
        repo_p = ProblemaLaboratorRepository()
        sortari = Sortari()

        # Populate dependencies
        repo_s.add(Student(1, "S", 10))
        repo_p.add(ProblemaLaborator((1, 1), "P", 2))

        self.srv = ServiceNota(repo_n, val_n, repo_s, repo_p, sortari)

    def test_flux_complet(self):
        self.srv.assign(1, (1, 1))
        self.srv.notare(1, (1, 1), 10)

        stats = self.srv.statistica_problema_nota((1, 1), 1)
        self.assertEqual(len(stats), 1)
        self.assertEqual(stats[0]['nota'], 10)