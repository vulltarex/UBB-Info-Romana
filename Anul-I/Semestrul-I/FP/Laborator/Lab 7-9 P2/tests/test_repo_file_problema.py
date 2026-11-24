import unittest
import os
from repository.repo_problema_file import ProblemaFileRepository
from domain.problema import ProblemaLaborator


class TestRepoFileProblema(unittest.TestCase):
    def setUp(self):
        self.filename = "test_probleme.txt"
        with open(self.filename, "w") as f:
            f.write("")
        self.repo = ProblemaFileRepository(self.filename)

    def tearDown(self):
        if os.path.exists(self.filename):
            os.remove(self.filename)

    def test_save_load(self):
        p = ProblemaLaborator((1, 1), "File", 3)
        self.repo.add(p)

        repo2 = ProblemaFileRepository(self.filename)
        self.assertEqual(len(repo2.get_all()), 1)