import unittest
from repository.repo_problema import ProblemaLaboratorRepository, DuplicateError
from domain.problema import ProblemaLaborator

class TestRepoProblema(unittest.TestCase):
    def setUp(self):
        self.repo = ProblemaLaboratorRepository()

    def test_crud(self):
        p = ProblemaLaborator((1, 1), "D", 2)
        self.repo.add(p)
        self.assertEqual(len(self.repo.get_all()), 1)
        with self.assertRaises(DuplicateError):
            self.repo.add(p)