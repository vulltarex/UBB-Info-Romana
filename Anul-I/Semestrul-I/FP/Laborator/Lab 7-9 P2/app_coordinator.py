from controller.service_problema import ProblemaLaboratorService
from controller.service_student import StudentService
from controller.service_nota import ServiceNota
from domain.validator_problema import ValidatorProblemaLaborator
from domain.validator_student import ValidatorStudent
from domain.validator_nota import ValidatorNota

from repository.repo_student_file import *
from repository.repo_problema_file import *
from repository.repo_nota_file import *

from repository.repo_student_json import *
from repository.repo_problema_json import *
from repository.repo_nota_json import *

from utils.sortari import *

from ui.console import Console
from tests import run_all_tests

def run_tests():
    run_all_tests.run_all()

run_tests()

val_student = ValidatorStudent()
val_problema = ValidatorProblemaLaborator()
val_nota = ValidatorNota()
sortari = Sortari()

while True:
    cmd = Console.citire_int(Console.meniu_tip_repo())
    match cmd:
        case 1:
            repo_student = StudentJSONRepository("studenti.json")
            repo_problema = ProblemaJSONRepository("probleme.json")
            repo_nota = NotaJSONRepository("note.json")
            break
        case 2:
            repo_student = StudentFileRepository("studenti.txt")
            repo_problema = ProblemaFileRepository("probleme.txt")
            repo_nota = NotaFileRepository("note.txt")
            break
        case 3:
            repo_student = StudentRepository()
            repo_problema = ProblemaLaboratorRepository()
            repo_nota = RepoNota()
            break
        case _:
            print("Comanda invalida!")


srv_student = StudentService(repo_student, val_student)
srv_problema = ProblemaLaboratorService(repo_problema, val_problema)
srv_nota = ServiceNota(repo_nota, val_nota, repo_student, repo_problema, sortari)

console = Console(srv_student, srv_problema, srv_nota)
console.run()