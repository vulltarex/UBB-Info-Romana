from domain.student import Student
from repository.repo_student import StudentRepository

class StudentFileRepository(StudentRepository):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, "r") as f:
                for line in f:
                    parts = line.strip().split(",")
                    if len(parts) == 3:
                        student = Student(int(parts[0]), parts[1], int(parts[2]))
                        super().add(student)
        except FileNotFoundError:
            pass

    def __save_to_file(self):
        with open(self.__filename, "w") as f:
            for student in self.get_all():
                f.write(f"{student.get_id()},{student.get_nume()},{student.get_grupa()}\n")

    def add(self, student):
        super().add(student)
        self.__save_to_file()

    def remove(self, id_student):
        super().remove(id_student)
        self.__save_to_file()

    def update(self, student):
        super().update(student)
        self.__save_to_file()