from repository.repo import NotFoundError
from controller.service import BlacklistedError

class Console:
    def __init__(self, srv):
        self.__srv = srv

    def meniu(self):
        while True:
            print("""
                    1. Sterge din fisier
                    2. Actualizare durata si descriere
                    3. Afisare lista emisiuni
                    4. Orar
                    5. Blocare emisiune
                    6. Deblocare emisiune
                    0. Iesire
                """)
            command = int(input("Introduceti comanda:"))
            match command:
                case 1:
                    nume = input("Introduceti numele:")
                    tip = input("introduceti tipul:")
                    try:
                        self.__srv.sterge(nume, tip)
                        print("Emisiune stearsa cu succes!")
                    except NotFoundError:
                        print("Emisiunea nu exista")
                    except BlacklistedError:
                        print("Emisiune blocata")
                case 2:
                    nume = input("Introduceti numele:")
                    tip = input("introduceti tipul:")
                    durata = input("Introduceti durata:")
                    descriere = input("Introduceti descrierea:")
                    try:
                        self.__srv.update(nume, tip, durata, descriere)
                        print("Emisiune actualizata!")
                    except NotFoundError:
                        print("Emisiunea nu exista!")
                    except BlacklistedError:
                        print("Emisiune blocata")
                case 3:
                    emisiuni = self.__srv.get_all()
                    for emisiune in emisiuni:
                        print(emisiune)
                case 4:
                    ora_start = int(input("Introduceti ora de inceput:"))
                    ora_final = int(input("Introduceti ora de final:"))
                    orar = self.__srv.program_random(ora_start, ora_final)
                    print(f"{'Ora':<15} {'Nume':<24} {'Tip':<12} {'Descriere':<24}")
                    for emisiune in orar:
                        print(emisiune)
                case 5:
                    tip = input("Introduceti tipul pentru blocare:")
                    self.__srv.blacklist(tip)
                case 6:
                    tip = input("Introduceti tipul pentru deblocare:")
                    self.__srv.remove_blacklist(tip)
                case 0:
                    break