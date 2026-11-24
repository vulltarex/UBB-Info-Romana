from repository.repo_antrenamente import *

class RepoFileAntrenamente(RepoAntrenamente):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__read_from_file()

    def __read_from_file(self) -> None:
        """
        Citeste continutul fisierului cu antrenamente
        """
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line.strip()
                if line != "":
                    cod, tip, descriere, pret = line.split(',')
                    antrenament = Antrenament(int(cod.strip()), tip.strip(), descriere.strip(), int(pret.strip()))
                    self.add(antrenament)

    def store(self, antrenament: Antrenament):
        """
        Stocheaza un antrenament in fisier si in memorie
        :param antrenament: antrenamentul de stocat
        """
        super().add(antrenament)
        self.__save_to_file(antrenament)

    def __save_to_file(self, antrenament: Antrenament) -> None:
        """
        Stocheaza un antrenament in fisier
        :param antrenament: antrenamentul de stocat
        """
        with open(self.__filename, 'a') as f:
            f.write(f"{antrenament.get_cod()}, {antrenament.get_tip()}, {antrenament.get_descriere()}, {antrenament.get_pret()}\n")