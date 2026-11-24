import unittest
import os
from repository.repo_student_file import StudentFileRepository
from domain.student import Student


class TestRepoFileStudent(unittest.TestCase):
    def setUp(self):
        self.filename = "test_studenti.txt"
        with open(self.filename, "w") as f:
            f.write("")  # Clean file
        self.repo = StudentFileRepository(self.filename)

    def tearDown(self):
        if os.path.exists(self.filename):
            os.remove(self.filename)

    def test_save_load(self):
        s = Student(1, "FileTest", 200)
        self.repo.add(s)

        # Reload repo to check persistence
        repo2 = StudentFileRepository(self.filename)
        self.assertEqual(len(repo2.get_all()), 1)
        self.assertEqual(repo2.get_all()[0].get_nume(), "FileTest")