import unittest
from controller.service_student import StudentService
from repository.repo_student import StudentRepository
from domain.validator_student import ValidatorStudent

class TestServiceStudent(unittest.TestCase):
    def setUp(self):
        repo = StudentRepository()
        val = ValidatorStudent()
        self.srv = StudentService(repo, val)

    def test_add_valid(self):
        self.srv.add(1, "Test", 100)
        self.assertEqual(len(self.srv.get_all()), 1)