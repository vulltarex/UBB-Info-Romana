class DuplicateError(Exception):
    pass

class NotFoundError(Exception):
    pass

class RepoNota:
    def __init__(self):
        self.__note = {}

    def assign(self, nota):
        key = (nota.get_id_student(), nota.get_nr_lab_nr_prob())
        if key in self.__note:
            raise DuplicateError("Problema deja asignata studentului!")
        self.__note[key] = nota

    def update(self, nota):
        key = (nota.get_id_student(), nota.get_nr_lab_nr_prob())
        if key not in self.__note:
            raise NotFoundError("Studentul nu are aceasta problema asignata!")
        self.__note[key] = nota

    def get_all(self):
        return list(self.__note.values())