class Antrenament:
    def __init__(self, cod: int, tip: str, descriere: str, pret: int):
        self.__cod = cod
        self.__tip = tip
        self.__descriere = descriere
        self.__pret = pret

    def get_cod(self):
        return self.__cod

    def get_tip(self):
        return self.__tip

    def get_descriere(self):
        return self.__descriere

    def get_pret(self):
        return self.__pret

    def set_cod(self, cod: int):
        self.__cod = cod

    def set_tip(self, tip):
        self.__tip = tip

    def set_descriere(self, descriere):
        self.__descriere = descriere

    def set_pret(self, pret):
        self.__pret = pret

    def __eq__(self, other):
        if not isinstance(other, Antrenament):
            return False
        if self.__cod != other.__cod:
            return False
        return True

    def __str__(self):
        return f"Cod: {self.__cod}, Tip: {self.__tip}, Descriere: {self.__descriere}, Pret per sesiune: {self.__pret}"