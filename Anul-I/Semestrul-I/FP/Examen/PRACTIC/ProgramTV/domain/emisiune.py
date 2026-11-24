class Emisiune:
    def __init__(self, nume, tip, durata, descriere):
        self.__nume = nume
        self.__tip = tip
        self.__durata = int(durata)
        self.__descriere = descriere

    def get_nume(self):
        return self.__nume

    def get_tip(self):
        return self.__tip

    def get_durata(self):
        return self.__durata

    def get_descriere(self):
        return self.__descriere

    def __str__(self):
        return f"{self.get_nume()},{self.get_tip()},{self.get_durata()},{self.get_descriere()}"

    def __eq__(self, other):
        if self.get_nume() == other.get_nume() and self.get_tip() == other.get_tip():
            return True
        return False