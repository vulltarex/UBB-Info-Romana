from domain.emisiune import Emisiune

class NotFoundError(Exception):
    pass

class RepoEmisiune:
    def __init__(self, filename):
        self.__emisiuni = []
        self.__filename = filename
        self.__load_from_file()

    def add(self, emisiune):
        self.__emisiuni.append(emisiune)

    def __load_from_file(self):
        try:
            with open(self.__filename, "r") as f:
                lines = f.readlines()
                for line in lines:
                    parts = [part.strip() for part in line.split(",")]
                    nume = parts[0]
                    tip = parts[1]
                    durata = parts[2]
                    descriere = parts[3]
                    emisiune = Emisiune(nume, tip, durata, descriere)
                    self.add(emisiune)
        except FileNotFoundError:
            pass

    def __save_to_file(self):
        with open(self.__filename, 'w') as f:
            for emisiune in self.__emisiuni:
                f.write(str(emisiune)+"\n")

    def remove(self, nume, tip):
        for emisiune in self.__emisiuni:
            if nume == emisiune.get_nume() and tip == emisiune.get_tip():
                self.__emisiuni.remove(emisiune)
                self.__save_to_file()
                return
        raise NotFoundError

    def update(self, emisiune):
        for index, em in enumerate(self.__emisiuni):
            if emisiune.get_nume() == em.get_nume() and emisiune.get_tip() == em.get_tip():
                self.__emisiuni[index] = emisiune
                self.__save_to_file()
                return
        raise NotFoundError


    def get_all(self):
        return self.__emisiuni