class Student:
    def __init__(self, id_student: int, nume: str, grupa: int):
        self.__id_student = id_student
        self.__nume = nume
        self.__grupa = grupa

    def get_nume(self):
        return self.__nume

    def get_id(self):
        return self.__id_student

    def get_grupa(self):
        return self.__grupa

    def set_nume(self, nume):
        self.__nume = nume

    def set_id(self, id_student):
        self.__id_student = id_student

    def set_grupa(self, grupa):
        self.__grupa = grupa

    def __str__(self):
        return f"ID: {self.__id_student}, Nume: {self.__nume}, Grupa: {self.__grupa}"

    def __eq__(self, other):
        return self.__id_student == other.get_id() and self.__nume == other.get_nume() and self.__grupa == other.get_grupa()
