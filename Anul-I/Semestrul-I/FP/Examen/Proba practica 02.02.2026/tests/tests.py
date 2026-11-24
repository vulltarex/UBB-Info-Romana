import unittest
from controller.service import *
from repository.repo import *

class Tests(unittest.TestCase):
    def setUp(self):
        self.__repo = RepoAutomobile("test.txt")
        self.__srv = Service(self.__repo)

    def testRepo(self):
        self.assertEqual(len(self.__repo.get_all()), 0)
        automobil = Automobil(1,"a",5,"b",datetime.date(2026,2,2))
        self.__repo.add(automobil)
        self.assertEqual(len(self.__repo.get_all()), 1)
        self.__repo.remove(automobil)
        self.assertEqual(len(self.__repo.get_all()), 0)

    def testService(self):
        self.assertEqual(len(self.__srv.get_all()), 0)
        automobil1 = Automobil(1, "a", 5, "b", datetime.date(2026, 2, 2))
        self.__srv.add(automobil1)
        self.assertEqual(len(self.__srv.get_all()), 1)
        self.__srv.remove(automobil1)
        self.assertEqual(len(self.__srv.get_all()), 0)

        self.assertEqual(self.__srv.contine_cifra(123, 4), False)
        self.assertEqual(self.__srv.contine_cifra(1234, 4), True)

        self.__srv.add(automobil1)
        self.__srv.remove_cifra(5)
        self.assertEqual(len(self.__srv.get_all()), 0)

        self.__srv.add(automobil1)
        automobil2 = Automobil(2, "abc", 6, "b", datetime.date(2025, 2, 2))
        automobil3 = Automobil(2, "*abc", 6, "b", datetime.date(2025, 2, 2))
        self.__srv.add(automobil2)
        self.assertEqual(self.__srv.filtrare("b", 5), [])
        self.assertEqual(self.__srv.filtrare("b", 7), [automobil3])
        self.assertEqual(self.__srv.filtrare("", -1), [automobil1, automobil3])

        automobil = Automobil(1, "a", 5, "b", datetime.date(2026, 2, 2))
        self.__srv.add(automobil)
        self.assertEqual(len(self.__srv.get_all()), 1)
        self.__repo.remove(automobil)
        self.assertEqual(len(self.__srv.get_all()), 0)

    def tearDown(self):
        with open("test.txt", 'w') as f:
            f.write("")

if __name__ == '__main__':
    unittest.main()
    print("Toate testele au trecut!")
