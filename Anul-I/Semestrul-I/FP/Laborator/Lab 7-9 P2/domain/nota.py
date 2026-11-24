class Nota:
    def __init__(self, id_student, nr_lab_nr_prob, val_nota):
        self.__id_student = id_student
        self.__nr_lab_nr_prob = nr_lab_nr_prob
        self.__val_nota = val_nota

    def get_id_student(self):
        return self.__id_student

    def get_nr_lab_nr_prob(self):
        return self.__nr_lab_nr_prob

    def get_val_nota(self):
        return self.__val_nota

    def __str__(self):
        return f"ID student: {self.__id_student}, Numar laborator, numar problema: {self.__nr_lab_nr_prob}, Nota: {self.__val_nota}"

    def __eq__(self, other):
        return self.__id_student == other.get_id_student() and self.__nr_lab_nr_prob == other.get_nr_lab_nr_prob()