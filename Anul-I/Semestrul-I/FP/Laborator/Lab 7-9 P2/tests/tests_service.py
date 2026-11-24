import unittest
from controller.service_student import StudentService
from controller.service_problema import ProblemaLaboratorService
from domain.problema import ProblemaLaborator
from domain.student import Student
from domain.validator_student import ValidatorStudent
from domain.validator_problema import ValidatorProblemaLaborator
from repository.repo_student import StudentRepository
from repository.repo_problema import ProblemaLaboratorRepository


class TestService(unittest.TestCase):
    def test_srv_student(self):
        repo = StudentRepository()
        validator = ValidatorStudent()
        srv = StudentService(repo, validator)

        srv.add(1, "Cristi", 212)
        self.assertEqual(srv.get_all(), [Student(1, "Cristi", 212)])

        srv.remove(1)
        self.assertEqual(srv.get_all(), [])

        srv.add(1, "Cristi", 212)
        srv.update(1, "Cristi", 555)
        self.assertEqual(srv.get_all(), [Student(1, "Cristi", 555)])
        self.assertEqual(srv.find_by_id(1), Student(1, "Cristi", 555))

        with self.assertRaises(Exception):
            srv.add("a", "Cristi", 212)

        with self.assertRaises(Exception):
            srv.remove("a")

        with self.assertRaises(Exception):
            srv.update("a", "Cristi", 555)

        with self.assertRaises(Exception):
            srv.find_by_id("a")

    def test_srv_probleme(self):
        repo = ProblemaLaboratorRepository()
        validator = ValidatorProblemaLaborator()
        srv = ProblemaLaboratorService(repo, validator)

        srv.add(1, 1, "Rezolvati problema", 12)
        self.assertEqual(srv.get_all(), [ProblemaLaborator((1, 1), "Rezolvati problema", 12)])

        srv.remove((1, 1))
        self.assertEqual(srv.get_all(), [])

        srv.add(1, 1, "Rezolvati problema", 12)
        srv.update((1, 1), "Rezolvati problema", 5)
        self.assertEqual(srv.get_all(), [ProblemaLaborator((1, 1), "Rezolvati problema", 5)])
        self.assertEqual(srv.find_by_numar_lab_nr_prob((1, 1)), ProblemaLaborator((1, 1), "Rezolvati problema", 5))

        with self.assertRaises(Exception):
            srv.find_by_numar_lab_nr_prob((2, 2))

        with self.assertRaises(Exception):
            srv.add(1, 1, "Rezolvati problema", "a")

        with self.assertRaises(Exception):
            srv.remove((2, 2))

        with self.assertRaises(Exception):
            srv.update((2, 2), "Rezolvati problema", 5)