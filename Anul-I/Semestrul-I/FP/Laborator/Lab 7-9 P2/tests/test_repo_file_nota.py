import unittest
import os
from repository.repo_nota_file import NotaFileRepository
from domain.nota import Nota


class TestRepoFileNota(unittest.TestCase):
    def setUp(self):
        self.filename = "test_note.txt"
        with open(self.filename, "w") as f:
            f.write("")
        self.repo = NotaFileRepository(self.filename)

    def tearDown(self):
        if os.path.exists(self.filename):
            os.remove(self.filename)

    def test_save_load(self):
        n = Nota(1, (1, 1), 8.50)
        self.repo.assign(n)

        repo2 = NotaFileRepository(self.filename)
        self.assertEqual(len(repo2.get_all()), 1)
        self.assertEqual(repo2.get_all()[0].get_val_nota(), 8.50)