class Console:
    def __init__(self, srv_student, srv_problema_laborator, srv_nota):
        self.__srv_student = srv_student
        self.__srv_problema_laborator = srv_problema_laborator
        self.__srv_nota = srv_nota

    @staticmethod
    def citire_int(mesaj: str):
        while True:
            try:
                val = int(input(mesaj))
                return val
            except ValueError:
                print("Introduceti un numar intreg!")

    # operatii student

    def add_student(self):
        id_student = self.citire_int("ID student: ")
        nume = input("Nume: ")
        grupa = self.citire_int("Grupa: ")
        try:
            self.__srv_student.add(id_student, nume, grupa)
            print("Studentul a fost adaugat!")
        except Exception as e:
            print(e)

    def remove_student(self):
        id_student = self.citire_int("ID student: ")
        try:
            self.__srv_student.remove(id_student)
            print("Studentul a fost sters!")
        except Exception as e:
            print(e)

    def update_student(self):
        id_student = self.citire_int("ID student: ")
        nume = input("Nume: ")
        grupa = self.citire_int("Grupa: ")
        try:
            self.__srv_student.update(id_student, nume, grupa)
            print("Studentul a fost actualizat!")
        except Exception as e:
            print(e)

    def print_students(self):
        students = self.__srv_student.get_all()
        for student in students:
            print(student)

    def find_student(self):
        id_student = self.citire_int("ID student: ")
        try:
            student = self.__srv_student.find_by_id(id_student)
            print(student)
        except Exception as e:
            print(e)

    def add_random_students(self):
        nr_studenti = self.citire_int("Numar studenti: ")
        self.__srv_student.add_random_students(nr_studenti)
        print("Studenti au fost adaugati!")

    # operatii probleme laborator

    def add_problema_laborator(self):
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        descriere = input("Descriere: ")
        deadline = self.citire_int("Deadline: ")
        try:
            self.__srv_problema_laborator.add(numar_lab, nr_prob, descriere, deadline)
            print("Problema laboratorului a fost adaugata!")
        except Exception as e:
            print(e)

    def remove_problema_laborator(self):
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        try:
            self.__srv_problema_laborator.remove((numar_lab, nr_prob))
            print("Problema a fost stearsa!")
        except Exception as e:
            print(e)

    def update_problema_laborator(self):
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        descriere = input("Descriere: ")
        deadline = self.citire_int("Deadline: ")
        try:
            self.__srv_problema_laborator.update((numar_lab, nr_prob), descriere, deadline)
            print("Problema a fost actualizata!")
        except Exception as e:
            print(e)

    def print_problema_laborator(self):
        problema_laborator = self.__srv_problema_laborator.get_all()
        for problema_laborator in problema_laborator:
            print(problema_laborator)

    def find_problema_laborator(self):
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        try:
            problema_laborator = self.__srv_problema_laborator.find_by_numar_lab_nr_prob((numar_lab, nr_prob))
            print(problema_laborator)
        except Exception as e:
            print(e)

    def add_random_probleme(self):
        numar_probleme = self.citire_int("Numar probleme: ")
        self.__srv_problema_laborator.add_random_probleme(numar_probleme)
        print("Problemele au fost adaugate!")

    # gestionare probleme/note
    def asignare_problema(self):
        id_student = self.citire_int("ID student: ")
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        try:
            self.__srv_nota.assign(id_student, (numar_lab, nr_prob))
            print("Problema a fost asignata!")
        except Exception as e:
            print(e)

    def notare_lab(self):
        id_student = self.citire_int("ID student: ")
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        val_nota = self.citire_int("Valoarea nota: ")
        try:
            self.__srv_nota.notare(id_student, (numar_lab, nr_prob), val_nota)
            print("Problema a fost notata!")
        except Exception as e:
            print(e)

    # creare rapoarte
    def statistica_problema_nota(self, cmd):
        numar_lab = self.citire_int("Numar laborator: ")
        nr_prob = self.citire_int("Numar problema: ")
        try:
            raport = self.__srv_nota.statistica_problema_nota((numar_lab, nr_prob), cmd)
            print(raport)
        except Exception as e:
            print(e)

    def raport_medie_sub5(self):
        try:
            raport = self.__srv_nota.raport_medie_sub5()
            print(raport)
        except Exception as e:
            print(e)

    def raport_probleme_facute(self):
        try:
            raport = self.__srv_nota.raport_probleme_facute()
            print(raport)
        except Exception as e:
            print(e)

    # meniuri
    @staticmethod
    def meniu_tip_repo():
        return """Alegeti modalitatea de stocare a datelor:
        1. Fisier JSON
        2. Fisier TXT
        3. Memorie
        """

    def meniu_studenti(self):
        while True:
            print("1. Adauga student")
            print("2. Sterge student")
            print("3. Modifica student")
            print("4. Cauta student")
            print("5. Afiseaza studentii")
            print("6. Adauga studenti aleatorii")
            print("0. Meniu principal")
            optiune = self.citire_int("Optiune: ")
            match optiune:
                case 1:
                    self.add_student()
                case 2:
                    self.remove_student()
                case 3:
                    self.update_student()
                case 4:
                    self.find_student()
                case 5:
                    self.print_students()
                case 6:
                    self.add_random_students()
                case 0:
                    break
                case _:
                    print("Comanda invalida!")

    def meniu_problema_laborator(self):
        while True:
            print("1. Adauga problema")
            print("2. Sterge problema")
            print("3. Modifica problema")
            print("4. Cauta problema")
            print("5. Afiseaza problemele")
            print("6. Adauga probleme aleatorii")
            print("0. Meniu principal")
            optiune = self.citire_int("Optiune: ")
            match optiune:
                case 1:
                    self.add_problema_laborator()
                case 2:
                    self.remove_problema_laborator()
                case 3:
                    self.update_problema_laborator()
                case 4:
                    self.find_problema_laborator()
                case 5:
                    self.print_problema_laborator()
                case 6:
                    self.add_random_probleme()
                case 0:
                    break
                case _:
                    print("Comanda invalida!")

    def meniu_statistica(self):
        while True:
            print("1. Ordonat descrescator dupa nota")
            print("2. Ordonat alfabetic")
            print("0. Inapoi la meniu principala")
            optiune = self.citire_int("Optiune: ")
            match optiune:
                case 1:
                    self.statistica_problema_nota(1)
                case 2:
                    self.statistica_problema_nota(2)
                case 0:
                    break
                case _:
                    print("Comanda invalida!")

    def meniu_raport(self):
        while True:
            print("1. Statistica la o problema")
            print("2. Studentii cu media sub 5")
            print("3. Leaderboard probleme facute")
            print("0. Meniu principal")
            optiune = self.citire_int("Optiune: ")
            match optiune:
                case 1:
                    self.meniu_statistica()
                case 2:
                    self.raport_medie_sub5()
                case 3:
                    self.raport_probleme_facute()
                case 0:
                    break
                case _:
                    print("Comanda invalida!")


    def meniu_principal(self):
        while True:
            print("1. Gestionare studenti")
            print("2. Gestionare probleme laborator")
            print("3. Asignare problema")
            print("4. Notare laborator")
            print("5. Creare raport")
            print("0. Inchide program")
            optiune = self.citire_int("Optiune: ")
            match optiune:
                case 1:
                    self.meniu_studenti()
                case 2:
                    self.meniu_problema_laborator()
                case 3:
                    self.asignare_problema()
                case 4:
                    self.notare_lab()
                case 5:
                    self.meniu_raport()
                case 0:
                    break
                case _:
                    print("Comanda invalida!")

    def run(self):
        self.meniu_principal()

