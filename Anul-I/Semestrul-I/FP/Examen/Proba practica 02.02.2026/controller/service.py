import datetime

from domain.automobil import Automobil

class Service:
    def __init__(self, repo):
        self.__repo = repo

    def add(self, automobil: Automobil) -> None:
        """
        Adauga un automobil in repo
        :param automobil: obiect de tip Automobil
        :return: None
        """
        self.__repo.add(automobil)

    def remove(self, automobil: Automobil) -> None:
        """
        Sterge un automobil din repo
        :param automobil: obiect de tip Automobil
        :return: None
        """
        self.__repo.remove(automobil)

    def get_all(self):
        """
        Returneaza toate automobilele stocate
        :return: lista cu automobilele stocate
        """
        return self.__repo.get_all()

    @staticmethod
    def contine_cifra(nr: int, cifra: int) -> bool:
        """
        Verifica daca un numar dat contine cifra data
        :param nr: numar natural nenul
        :param cifra: o cifra (0 <= cifra <= 10)
        :return: True/False in functie de indeplinirea conditiei
        """
        while nr > 0:
            if nr % 10 == cifra:
                return True
            nr //= 10
        return False

    def remove_cifra(self, cifra: int) -> int:
        """
        Sterge automobilele stocate ce contin cifra data in pretul lor
        :param cifra: cifra data pentru cautare (0 <= cifra <= 9)
        :return: cnt - numarul de automobile sterse
        """
        automobile = list(self.get_all())
        cnt = 0
        for automobil in automobile:
            if self.contine_cifra(automobil.get_pret(), cifra):
                self.remove(automobil)
                cnt += 1
        return cnt

    def filtrare(self, text: str, val: int) -> list:
        """
        Returneaza o lista filtrata in functie de parametrii. Lista filtrata include automobilele ce contin sirul din parametrul text
        in marca si care au pretul mai mic decat parametrul val. Daca val = -1, nu se tine cont de filtrarea de pret
        :param text: un string pentru filtrare
        :param val: numar intreg (val >= -1)
        :return: dto - lista cu automobilele filtrate
        """
        dto = []
        automobile = list(self.get_all())
        if val == -1:
            dto = [automobil for automobil in automobile if text in automobil.get_marca()]
        else:
            dto = [automobil for automobil in automobile if text in automobil.get_marca() and automobil.get_pret() < val]
        for index, automobil in enumerate(dto):
            if automobil.get_data() < datetime.date.today():
                dto[index]._Automobil__marca = "*" + automobil.get_marca()
        return dto

    def undo(self) -> None:
        """
        Readuce repo-ul si fisierul la starea anterioara
        :return: None
        """
        self.__repo.undo()