import unittest
from repository.repo_student import StudentRepository, DuplicateError, NotFoundError
from domain.student import Student

class TestRepoStudent(unittest.TestCase):
    def setUp(self):
        self.repo = StudentRepository()

    def test_add_remove(self):
        s = Student(1, "A", 10)
        self.repo.add(s)
        self.assertEqual(len(self.repo.get_all()), 1)
        self.repo.remove(1)
        self.assertEqual(len(self.repo.get_all()), 0)

    def test_duplicate(self):
        s = Student(1, "A", 10)
        self.repo.add(s)
        with self.assertRaises(DuplicateError):
            self.repo.add(s)