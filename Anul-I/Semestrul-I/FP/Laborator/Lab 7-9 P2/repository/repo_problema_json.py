import json
from domain.problema import ProblemaLaborator
from repository.repo_problema import ProblemaLaboratorRepository

class ProblemaJSONRepository(ProblemaLaboratorRepository):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, "r") as f:
                data = json.load(f)
                for item in data:
                    # JSON transforma tuple in liste, trebuie convertit inapoi in tuple
                    nr_lab_nr_prob = tuple(item['id_problema'])
                    prob = ProblemaLaborator(nr_lab_nr_prob, item['descriere'], item['deadline'])
                    super().add(prob)
        except (FileNotFoundError, json.JSONDecodeError):
            pass

    def __save_to_file(self):
        lista = []
        for prob in self.get_all():
            lista.append({
                "id_problema": prob.get_numar_lab_nr_prob(),
                "descriere": prob.get_descriere(),
                "deadline": prob.get_deadline()
            })
        with open(self.__filename, "w") as f:
            json.dump(lista, f, indent=4)

    def add(self, prob):
        super().add(prob)
        self.__save_to_file()

    def remove(self, id_prob):
        super().remove(id_prob)
        self.__save_to_file()

    def update(self, prob):
        super().update(prob)
        self.__save_to_file()