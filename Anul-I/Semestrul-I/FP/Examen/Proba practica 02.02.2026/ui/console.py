from domain.automobil import Automobil
import datetime

from repository.repo import AlreadyExistsError, UndoError


class Console:
    def __init__(self, srv):
        self.__srv = srv

    def meniu(self):
        while True:
            print("""
            1. Adaugare automobil
            2. Stergere automobil
            3. Filtrare
            4. Undo
            5. Afisare toate
            0. Exit
            """)
            command = int(input("Introduceti comanda:"))
            match command:
                case 1:
                    id = int(input("Introduceti ID:"))
                    marca = input("Introduceti marca:")
                    pret = int(input("Introduceti pretul:"))
                    model = input("Introduceti modelul:")
                    zi = int(input("Introduceti ziua:"))
                    luna = int(input("Introduceti luna:"))
                    an = int(input("Introduceti anul:"))
                    automobil = Automobil(id, marca, pret, model, datetime.date(an,luna,zi))
                    try:
                        self.__srv.add(automobil)
                        print("Automobilul a fost adaugat!")
                    except AlreadyExistsError:
                        print("ID existent!")
                case 2:
                    cifra = int(input("Introduceti o cifra:"))
                    sterse = self.__srv.remove_cifra(cifra)
                    print(f"Au fost sterse {sterse} automobile.")
                case 3:
                    text = input("Introduceti un text:")
                    val = int(input("Introduceti un numar:"))
                    lista_filtrata = self.__srv.filtrare(text, val)
                    for automobil in lista_filtrata:
                        print(automobil)
                case 4:
                    try:
                        self.__srv.undo()
                        print("Operatie refacuta!")
                    except UndoError:
                        print("Nu exista operatii anterioare!")
                case 5:
                    automobile = self.__srv.get_all()
                    for automobil in automobile:
                        print(automobil)
                case 0:
                    break
                case _:
                    print("Introduceti o comanda valida!")