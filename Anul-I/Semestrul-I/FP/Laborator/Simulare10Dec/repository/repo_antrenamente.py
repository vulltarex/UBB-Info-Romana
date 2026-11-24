from domain.antrenament import Antrenament


class NotFoundError(Exception):
    pass

class AlreadyExistsError(Exception):
    pass

class RepoAntrenamente:
    def __init__(self):
        self.__antrenamente = {}

    def add(self, antrenament: Antrenament) -> None:
        """
        Adauga un antrenament in repo
        :param antrenament: un antrenament
        :raises AlreadyExistsError: antrenamentul exista deja in repo
        """
        if antrenament.get_cod() in self.__antrenamente:
            raise AlreadyExistsError("Antrenamentul exista deja!")
        self.__antrenamente[antrenament.get_cod()] = antrenament

    def find_by_id(self, cod: int) -> Antrenament:
        """
        Gaseste un antrenament dupa cod
        :param cod: codul antrenamentului
        :return: antrenamentul cu codul dat
        :raises NotFoundError: antrenamentul nu exista
        """
        if cod not in self.__antrenamente:
            raise NotFoundError("Antrenamentul nu exista!")
        return self.__antrenamente[cod]

    def remove(self, cod: int) -> None:
        """
        Sterge un antrenament din repo
        :param cod: codul antrenamentului
        :raises NotFoundError: antrenamentul nu exista
        """
        if cod not in self.__antrenamente:
            raise NotFoundError("Antrenamentul nu exista!")
        del self.__antrenamente[cod]

    def update(self, cod: int, antrenament: Antrenament) -> None:
        """
        Actualizeaza un antrenament din repo
        :param cod: codul antrenamentului
        :param antrenament: antrenamentul nou
        :raises NotFoundError: antrenamentul nu exista
        """
        if cod not in self.__antrenamente:
            raise NotFoundError("Antrenamentul nu exista!")
        self.__antrenamente[cod] = antrenament

    def get_all(self):
        """
        Returneaza toate antrenamentele din repo
        :return: Toate antrenamentele din repo
        """
        return self.__antrenamente.values()