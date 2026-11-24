from domain.nota import Nota
from domain.validator_nota import *
from utils.sortari import *

class ServiceNota:
    def __init__(self, repo_nota, validator_nota, repo_student, repo_problema, sortari):
        self.__repo_nota = repo_nota
        self.__validator_nota = validator_nota
        self.__repo_student = repo_student
        self.__repo_problema = repo_problema
        self.__sortari = sortari

    def assign(self, id_student, nr_lab_nr_prob):
        self.__repo_student.find_by_id(id_student)
        self.__repo_problema.find_by_numar_lab_nr_prob(nr_lab_nr_prob)

        nota = Nota(id_student, nr_lab_nr_prob, 0)
        self.__repo_nota.assign(nota)

    def notare(self, id_student, nr_lab_nr_prob, val_nota):
        nota = Nota(id_student, nr_lab_nr_prob, val_nota)
        self.__validator_nota.validate(nota)
        self.__repo_nota.update(nota)

    def statistica_problema_nota(self, nr_lab_nr_prob, cmd):
        note = []
        for nota in self.__repo_nota.get_all():
            if nota.get_nr_lab_nr_prob() == nr_lab_nr_prob and nota.get_val_nota() != 0:
                note.append(nota)
        raport = []
        for nota in note:
            student = self.__repo_student.find_by_id(nota.get_id_student())
            raport.append({'nume': student.get_nume(), 'nota': nota.get_val_nota()})

        if cmd == 1:
            self.__sortari.sort_bubble(raport, key=lambda x: x['nume'])
            return self.__sortari.sort_bubble(raport, key=lambda x: x['nota'], reverse=True)
        else:
            return self.__sortari.sort_shell(raport, key=lambda x: (x['nume'], x['nota']))

    def raport_medie_sub5(self):
        medii_lab = {}
        for nota in self.__repo_nota.get_all():
            if nota.get_val_nota() == 0:
                continue
            if nota.get_id_student() not in medii_lab:
                medii_lab[nota.get_id_student()] = []
            medii_lab[nota.get_id_student()].append(nota.get_val_nota())

        rezultat = []
        for id_student, lista_note in medii_lab.items():
            if not lista_note:
                continue
            if sum(lista_note) / len(lista_note) < 5:
                student = self.__repo_student.find_by_id(id_student)
                rezultat.append({'nume': student.get_nume(), 'media': sum(lista_note) / len(lista_note)})
        return rezultat

    def raport_probleme_facute(self):
        statistica = {}
        for nota in self.__repo_nota.get_all():
            if nota.get_val_nota() != 0:
                if nota.get_id_student() not in statistica:
                    statistica[nota.get_id_student()] = 1
                else:
                    statistica[nota.get_id_student()] += 1

        rezultat = []
        for id_student, nr_probleme in statistica.items():
            student = self.__repo_student.find_by_id(id_student)
            rezultat.append({'nume': student.get_nume(), 'nr_probleme': nr_probleme})
        self.__sortari.sort_bubble(rezultat, key=lambda x: x['nume'])
        return self.__sortari.sort_bubble(rezultat, key = lambda x: x['nr_probleme'], reverse = True)