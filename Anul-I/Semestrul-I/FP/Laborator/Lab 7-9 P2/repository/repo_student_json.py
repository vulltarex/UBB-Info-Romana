import json
from domain.student import Student
from repository.repo_student import StudentRepository

class StudentJSONRepository(StudentRepository):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, "r") as f:
                data = json.load(f)
                for item in data:
                    student = Student(item['id'], item['nume'], item['grupa'])
                    super().add(student)
        except (FileNotFoundError, json.JSONDecodeError):
            pass

    def __save_to_file(self):
        lista = []
        for student in self.get_all():
            lista.append({
                "id": student.get_id(),
                "nume": student.get_nume(),
                "grupa": student.get_grupa()
            })
        with open(self.__filename, "w") as f:
            json.dump(lista, f, indent=4)

    def add(self, student):
        super().add(student)
        self.__save_to_file()

    def remove(self, id_student):
        super().remove(id_student)
        self.__save_to_file()

    def update(self, student):
        super().update(student)
        self.__save_to_file()