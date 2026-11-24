import random

from repository.repo import *

class BlacklistedError(Exception):
    pass

class Service:
    def __init__(self, repo):
        self.__repo = repo
        self.__emisiuni_blocate = []

    def sterge(self, nume, tip):
        if tip not in self.__emisiuni_blocate:
            self.__repo.remove(nume, tip)
        else:
            raise BlacklistedError

    def get_all(self):
        return self.__repo.get_all()

    def update(self, nume, tip, durata, descriere):
        if tip not in self.__emisiuni_blocate:
            emisiune = Emisiune(nume, tip, durata, descriere)
            self.__repo.update(emisiune)
        else:
            raise BlacklistedError

    def blacklist(self, tip):
        self.__emisiuni_blocate.append(tip)

    def remove_blacklist(self, tip):
        self.__emisiuni_blocate.remove(tip)

    def program_random(self, ora_start, ora_final):
        timp_disponibil = ora_final - ora_start
        emisiuni_disponibile = self.get_all()
        timp_scurs = 0
        lista_program = []
        while timp_disponibil and len(emisiuni_disponibile) != 0:
            candidat = random.choice(emisiuni_disponibile)
            if candidat.get_durata() <= timp_disponibil and candidat.get_tip() not in self.__emisiuni_blocate:
                lista_program.append(f"{ora_start + timp_scurs} {candidat.get_nume()} {candidat.get_tip()} {candidat.get_descriere()}")
                timp_scurs += candidat.get_durata()
                timp_disponibil -= candidat.get_durata()
                emisiuni_disponibile.remove(candidat)

        while timp_disponibil:
            try:
                candidat = random.choice(self.get_all())
            except IndexError:
                print(self.get_all())
            if candidat.get_durata() <= timp_disponibil and candidat.get_tip() not in self.__emisiuni_blocate:
                candidat = Emisiune(candidat.get_nume(), candidat.get_tip(), candidat.get_durata(), "*****")
                timp_disponibil -= candidat.get_durata()
                lista_program.append(f"{ora_start + timp_scurs} {candidat.get_nume()} {candidat.get_tip()} {candidat.get_descriere()}")
                timp_scurs += candidat.get_durata()

        return lista_program