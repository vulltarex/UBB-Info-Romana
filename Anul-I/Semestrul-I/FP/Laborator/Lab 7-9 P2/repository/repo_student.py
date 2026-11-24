class NotFoundError(Exception):
    pass

class DuplicateError(Exception):
    pass

class StudentRepository:
    def __init__(self):
        self.__students = {}

    def add(self, student):
        if student.get_id() in self.__students:
            raise DuplicateError(f"Studentul cu id-ul {student.get_id()} exista deja!")
        self.__students[student.get_id()] = student

    def remove(self, id_student):
        if id_student not in self.__students:
            raise NotFoundError(f"Studentul cu id-ul {id_student} nu exista!")
        del self.__students[id_student]

    def update(self, student):
        if student.get_id() not in self.__students:
            raise NotFoundError(f"Studentul cu id-ul {student.get_id()} nu exista!")
        self.__students[student.get_id()] = student

    def find_by_id(self, id_student):
        if id_student not in self.__students:
            raise NotFoundError(f"Studentul cu id-ul {id_student} nu exista!")
        return self.__students[id_student]

    def get_all(self):
        return list(self.__students.values())