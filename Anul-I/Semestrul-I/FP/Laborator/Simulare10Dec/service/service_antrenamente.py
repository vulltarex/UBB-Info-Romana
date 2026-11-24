from repository.repo_file_antrenamente import *
from domain.antrenament import *
from domain.validator_antrenament import *

class ServiceAntrenamente:
    def __init__(self, repo: RepoFileAntrenamente, val: ValidatorAntrenament):
        self.__repo = repo
        self.__val = val

    def add(self, antrenament: Antrenament) -> None:
        """
        Adauga un antrenament in repo
        :param antrenament: antrenamentul de adaugat
        """
        self.__val.validate(antrenament)
        self.__repo.store(antrenament)

    def remove(self, cod: int) -> None:
        """
        Sterge un antrenament din repo
        :param cod: codul antrenamentului
        """
        self.__repo.remove(cod)

    def update(self, cod: int, antrenament: Antrenament) -> None:
        """
        Actualizeaza un antrenament din repo
        :param cod: codul antrenamentului de actualizat
        :param antrenament: antrenamentul nou
        """
        self.__val.validate(antrenament)
        self.__repo.update(cod, antrenament)

    def find_by_cod(self, cod: int) -> Antrenament:
        """
        Cauta si returneaza un antrenament dupa cod
        :param cod: codul antrenamentului cautat
        :return: antrenamentul cautat
        """
        return self.__repo.find_by_id(cod)

    def get_all(self):
        """
        returneaza toate antrenamentele din repo
        :return: toate antrenamentele din repo
        """
        return self.__repo.get_all()

    def find_by_tip(self, tip: str):
        """
        Returneaza toate antrenamentele ce contin sirul de caractere transmis
        :param tip: tipul cautat
        :return: antrenamentele ce contine tipul dat
        """
        dto = []
        for antr in self.__repo.get_all():
            if antr.get_tip().upper().find(tip.upper()) != -1:
                dto.append(antr)
        return dto

    def rezervare(self, cod: int, nr_sesiuni: int) -> tuple:
        """
        Returneaza un antrenament si pretul total pentru sesiunile rezervate
        :param cod: codul antrenamentului
        :param nr_sesiuni: numarul de sesiuni rezervate
        :return: antrenamentul si pretul total
        """
        antrenament = self.find_by_cod(cod)
        pret = antrenament.get_pret() * nr_sesiuni
        return antrenament, pret