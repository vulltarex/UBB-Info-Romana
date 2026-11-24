import unittest
from domain.problema import ProblemaLaborator
from domain.student import Student
from repository.repo_student import StudentRepository, DuplicateError, NotFoundError
from repository.repo_problema import ProblemaLaboratorRepository

class TestRepo(unittest.TestCase):
    def test_repo_studenti(self):
        repo = StudentRepository()
        student = Student(1, "Cristi", 212)

        repo.add(student)
        self.assertEqual(repo.get_all(), [student])

        repo.remove(1)
        self.assertEqual(repo.get_all(), [])

        repo.add(student)
        student_nou = Student(1, "Cristi", 555)
        repo.update(student_nou)
        self.assertEqual(repo.get_all(), [student_nou])
        self.assertEqual(repo.find_by_id(1), student_nou)

        with self.assertRaises(NotFoundError):
            repo.find_by_id(2)

        with self.assertRaises(DuplicateError):
            repo.add(Student(1, "Cristi", 212))

        with self.assertRaises(NotFoundError):
            repo.remove(2)

        with self.assertRaises(NotFoundError):
            repo.update(Student(2, "Cristi", 555))

    def test_repo_probleme(self):
        repo = ProblemaLaboratorRepository()
        problema = ProblemaLaborator((1, 1), "Rezolvati problema", 12)

        repo.add(problema)
        self.assertEqual(repo.get_all(), [problema])

        repo.remove((1, 1))
        self.assertEqual(repo.get_all(), [])

        repo.add(problema)
        prob_noua = ProblemaLaborator((1, 1), "Rezolvati problema", 5)
        repo.update(prob_noua)
        self.assertEqual(repo.get_all(), [prob_noua])
        self.assertEqual(repo.find_by_numar_lab_nr_prob((1, 1)), prob_noua)

        with self.assertRaises(NotFoundError):
            repo.find_by_numar_lab_nr_prob((2, 2))

        with self.assertRaises(DuplicateError):
            repo.add(ProblemaLaborator((1, 1), "Rezolvati problema", 12))

        with self.assertRaises(NotFoundError):
            repo.remove((2, 2))

        with self.assertRaises(NotFoundError):
            repo.update(ProblemaLaborator((2, 2), "Rezolvati problema", 12))