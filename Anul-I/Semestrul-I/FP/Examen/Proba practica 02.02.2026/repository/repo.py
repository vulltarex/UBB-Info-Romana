from domain.automobil import Automobil
import datetime
from copy import deepcopy

class UndoError(Exception):
    pass

class AlreadyExistsError(Exception):
    pass

class NotFoundError(Exception):
    pass

class RepoAutomobile:
    def __init__(self, filename = "automobile.txt"):
        self.__automobile = {}
        self.__history = []
        self.__load_from_file(filename)
        self.__filename = filename

    def update_history(self) -> None:
        """
        Actualizeaza istoricul repository-ului
        :return: None
        """
        self.__history.append(deepcopy(self.__automobile))

    def __load_from_file(self, filename: str) -> None:
        """
        Incarca datele din fisier in memorie
        :param filename: numele fisierului - str
        :return: None
        """
        with open(filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                parts = [p.strip() for p in line.split(',')]
                id = int(parts[0])
                marca = parts[1]
                pret = int(parts[2])
                model = parts[3]
                data = parts[4].split(':')
                automobil = Automobil(id, marca, pret, model, datetime.date(int(data[2]),int(data[1]),int(data[0])))
                self.__automobile[id] = automobil

    def __save_to_file(self, filename: str) -> None:
        """
        Salveaza automobilele din memorie in fisier
        :param filename: numele fisierului - str
        :return: None
        """
        with open(filename, "w") as f:
            for automobil in self.__automobile.values():
                f.write(str(automobil)+"\n")

    def add(self, automobil: Automobil) -> None:
        """
        Adauga un obiect de tip Automobil in repo, actualizeaza istoricul si salveaza in fisier
        :param automobil: obiect de tip Automobil
        :return: None
        :raises: AlreadyExistsError - daca exista deja un automobil cu ID-ul celui transmis ca parametru in repo
        """
        if automobil.get_id() not in self.__automobile.keys():
            self.update_history()
            self.__automobile[automobil.get_id()] = automobil
            self.__save_to_file(self.__filename)
        else:
            raise AlreadyExistsError

    def remove(self, automobil: Automobil) -> None:
        """
        Sterge un automobil din repo, actualizeaza istoricul si salveaza in fisier
        :param automobil: obiect de tip Automobil
        :return: None
        :raises: NotFounderror - daca nu exista niciun automobil cu ID-ul celui transmis ca parametru
        """
        if automobil.get_id() in self.__automobile.keys():
            self.update_history()
            self.__automobile.pop(automobil.get_id())
            self.__save_to_file(self.__filename)
        else:
            raise NotFoundError

    def get_all(self):
        """
        Returneaza valorile tuturor automobilelor din repo
        :return: automobile.values() - dict_values
        """
        return self.__automobile.values()

    def undo(self) -> None:
        """
        Readuce repo-ul si fisierul la starea anterioara
        :return: None
        :raises: UndoError - daca nu exista versiuni anterioare
        """
        if len(self.__history) == 0:
            raise UndoError
        self.__automobile = deepcopy(self.__history.pop())
        self.__save_to_file(self.__filename)