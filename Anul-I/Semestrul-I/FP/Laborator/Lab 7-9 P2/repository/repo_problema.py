class NotFoundError(Exception):
    pass

class DuplicateError(Exception):
    pass

class ProblemaLaboratorRepository:
    def __init__(self):
        self.__probleme_laborator = {}

    def add(self, problema_laborator):
        if problema_laborator.get_numar_lab_nr_prob() in self.__probleme_laborator:
            raise DuplicateError(f"Problema cu numarul {problema_laborator.get_numar_lab_nr_prob()[1]}, laboratorul {problema_laborator.get_numar_lab_nr_prob()[0]} exista deja!")
        self.__probleme_laborator[problema_laborator.get_numar_lab_nr_prob()] = problema_laborator

    def remove(self, numar_lab_nr_prob):
        if numar_lab_nr_prob not in self.__probleme_laborator:
            raise NotFoundError(f"Problema cu numarul {numar_lab_nr_prob[1]}, laboratorul {numar_lab_nr_prob[0]} nu exista!")
        del self.__probleme_laborator[numar_lab_nr_prob]

    def update(self, problema_laborator):
        if problema_laborator.get_numar_lab_nr_prob() not in self.__probleme_laborator:
            raise NotFoundError(f"Problema cu numarul {problema_laborator.get_numar_lab_nr_prob()[1]}, laboratorul {problema_laborator.get_numar_lab_nr_prob()[0]} nu exista!")
        self.__probleme_laborator[problema_laborator.get_numar_lab_nr_prob()] = problema_laborator

    def find_by_numar_lab_nr_prob(self, numar_lab_nr_prob):
        if numar_lab_nr_prob not in self.__probleme_laborator:
            raise NotFoundError(f"Problema cu numarul {numar_lab_nr_prob[1]}, laboratorul {numar_lab_nr_prob[0]} nu exista!")
        return self.__probleme_laborator[numar_lab_nr_prob]

    def get_all(self):
        return list(self.__probleme_laborator.values())