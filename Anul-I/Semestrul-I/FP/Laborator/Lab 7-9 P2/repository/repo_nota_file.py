from domain.nota import Nota
from repository.repo_nota import RepoNota

class NotaFileRepository(RepoNota):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, "r") as f:
                for line in f:
                    parts = line.strip().split(",")
                    if len(parts) == 4:
                        id_student = int(parts[0])
                        nr_lab = int(parts[1])
                        nr_prob = int(parts[2])
                        valoare = float(parts[3])
                        nota = Nota(id_student, (nr_lab, nr_prob), valoare)
                        # Accesam dictionarul direct pentru a evita verificarea de duplicate la load
                        key = (id_student, (nr_lab, nr_prob))
                        self._RepoNota__note[key] = nota
        except FileNotFoundError:
            pass

    def __save_to_file(self):
        with open(self.__filename, "w") as f:
            for nota in self.get_all():
                lab, nr = nota.get_nr_lab_nr_prob()
                f.write(f"{nota.get_id_student()},{lab},{nr},{nota.get_val_nota()}\n")

    def assign(self, nota):
        super().assign(nota)
        self.__save_to_file()

    def update(self, nota):
        super().update(nota)
        self.__save_to_file()