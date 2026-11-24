class ProblemaLaborator:
    def __init__(self, numar_lab_nr_prob: tuple, descriere: str, deadline: int):
        self.__numar_lab_nr_prob = numar_lab_nr_prob
        self.__descriere = descriere
        self.__deadline = deadline

    def get_numar_lab_nr_prob(self):
        return self.__numar_lab_nr_prob

    def get_descriere(self):
        return self.__descriere

    def get_deadline(self):
        return self.__deadline

    def set_numar_lab_nr_prob(self, numar_lab_nr_prob):
        self.__numar_lab_nr_prob = numar_lab_nr_prob

    def set_descriere(self, descriere):
        self.__descriere = descriere

    def set_deadline(self, deadline):
        self.__deadline = deadline

    def __str__(self):
        return f"Numar laborator, numar problema: {self.__numar_lab_nr_prob}, Descriere: {self.__descriere}, Deadline: saptamana {self.__deadline}"

    def __eq__(self, other):
        return self.__numar_lab_nr_prob == other.get_numar_lab_nr_prob() and self.__descriere == other.get_descriere() and self.__deadline == other.get_deadline()
