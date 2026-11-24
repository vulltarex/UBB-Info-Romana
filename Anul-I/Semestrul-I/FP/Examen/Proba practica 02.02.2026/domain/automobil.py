import datetime

class Automobil:
    def __init__(self, id, marca, pret, model, data):
        self.__id = id
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data = data

    def get_id(self) -> int:
        """
        Returneaza IDul automobilului
        :return: id - int
        """
        return self.__id

    def get_marca(self) -> str:
        """
        Returneaza marca automobilului
        :return: marca - str
        """
        return self.__marca

    def get_pret(self) -> int:
        """
        Returneaza pretul automobilului
        :return: pret - int
        """
        return self.__pret

    def get_model(self) -> str:
        """
        Returneaza modelul automobilului
        :return: model - str
        """
        return self.__model

    def get_data(self) -> datetime.date:
        """
        Returneaza data automobilului
        :return: data - date
        """
        return self.__data

    def __str__(self):
        return f"{self.get_id()},{self.get_marca()},{self.get_pret()},{self.get_model()},{self.get_data().day}:{self.get_data().month}:{self.get_data().year}"

    def __eq__(self, other):
        if not isinstance(other, Automobil):
            return False
        if self.get_id() != other.get_id():
            return False
        if self.get_marca() != other.get_marca():
            return False
        if self.get_pret() != other.get_pret():
            return False
        if self.get_model() != other.get_model():
            return False
        if self.get_data() != other.get_data():
            return False
        return True