import json
from domain.nota import Nota
from repository.repo_nota import RepoNota


class NotaJSONRepository(RepoNota):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, "r") as f:
                data = json.load(f)
                for item in data:
                    id_student = item['id_student']
                    # Convertim lista [lab, prob] inapoi in tuple (lab, prob)
                    nr_lab_nr_prob = tuple(item['id_problema'])
                    valoare = item['nota']

                    nota = Nota(id_student, nr_lab_nr_prob, valoare)
                    # Adaugam manual in dictionarul parintelui pentru a evita validarile la incarcare
                    key = (id_student, nr_lab_nr_prob)
                    self._RepoNota__note[key] = nota
        except (FileNotFoundError, json.JSONDecodeError):
            pass

    def __save_to_file(self):
        lista = []
        for nota in self.get_all():
            lista.append({
                "id_student": nota.get_id_student(),
                "id_problema": nota.get_nr_lab_nr_prob(),
                "nota": nota.get_val_nota()
            })
        with open(self.__filename, "w") as f:
            json.dump(lista, f, indent=4)

    def assign(self, nota):
        super().assign(nota)
        self.__save_to_file()

    def update(self, nota):
        super().update(nota)
        self.__save_to_file()