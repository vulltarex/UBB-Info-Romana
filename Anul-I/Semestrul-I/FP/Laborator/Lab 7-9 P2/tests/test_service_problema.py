import unittest
from controller.service_problema import ProblemaLaboratorService
from repository.repo_problema import ProblemaLaboratorRepository
from domain.validator_problema import ValidatorProblemaLaborator

class TestServiceProblema(unittest.TestCase):
    def setUp(self):
        repo = ProblemaLaboratorRepository()
        val = ValidatorProblemaLaborator()
        self.srv = ProblemaLaboratorService(repo, val)

    def test_add_valid(self):
        self.srv.add(1, 1, "D", 2)
        self.assertEqual(len(self.srv.get_all()), 1)