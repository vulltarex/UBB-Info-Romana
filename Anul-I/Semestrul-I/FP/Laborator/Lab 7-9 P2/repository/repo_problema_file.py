from domain.problema import ProblemaLaborator
from repository.repo_problema import ProblemaLaboratorRepository

class ProblemaFileRepository(ProblemaLaboratorRepository):
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
                        nr_lab = int(parts[0])
                        nr_prob = int(parts[1])
                        descriere = parts[2]
                        deadline = int(parts[3])
                        prob = ProblemaLaborator((nr_lab, nr_prob), descriere, deadline)
                        super().add(prob)
        except FileNotFoundError:
            pass

    def __save_to_file(self):
        with open(self.__filename, "w") as f:
            for prob in self.get_all():
                lab, nr = prob.get_numar_lab_nr_prob()
                f.write(f"{lab},{nr},{prob.get_descriere()},{prob.get_deadline()}\n")

    def add(self, problema):
        super().add(problema)
        self.__save_to_file()

    def remove(self, id_problema):
        super().remove(id_problema)
        self.__save_to_file()

    def update(self, problema):
        super().update(problema)
        self.__save_to_file()