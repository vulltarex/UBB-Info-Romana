import unittest
from domain.student import Student
from domain.problema import ProblemaLaborator
from domain.nota import Nota

class TestDomain(unittest.TestCase):
    def test_student(self):
        s = Student(1, "Ana", 100)
        self.assertEqual(s.get_id(), 1)
        self.assertEqual(s.get_nume(), "Ana")
        self.assertEqual(s.get_grupa(), 100)

    def test_problema(self):
        p = ProblemaLaborator((1, 1), "Desc", 12)
        self.assertEqual(p.get_numar_lab_nr_prob(), (1, 1))
        self.assertEqual(p.get_descriere(), "Desc")
        self.assertEqual(p.get_deadline(), 12)

    def test_nota(self):
        n = Nota(1, (1, 1), 9)
        self.assertEqual(n.get_val_nota(), 9)
        self.assertEqual(n.get_nr_lab_nr_prob(), (1, 1))
        self.assertEqual(n.get_id_student(), 1)
