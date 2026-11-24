from domain.antrenament import Antrenament


class Console:
    def __init__(self, srv_antrenamente):
        self.__srv_antrenamente = srv_antrenamente

    @staticmethod
    def citire_int(msj: str) -> int | None:
        nr = input(msj)
        try:
            nr = int(nr)
            return nr
        except ValueError:
            print("Introduceti un numar intreg!")

    @staticmethod
    def print_main_menu() -> None:
        print("""
        1. Adaugare antrenament
        2. Stergere antrenament
        3. Cautare antrenament dupa cod
        4. Modificare antrenament
        5. Afisare toate antrenamentele
        6. Cautare antrenament dupa tip
        7. Rezervare antrenamente
        0. Iesire
        """)

    def __add_antrenament(self):
        cod = self.citire_int("Cod: ")
        tip = input("Tip: ")
        descriere = input("Descriere: ")
        pret = self.citire_int("Pret per sesiune: ")
        antrenament = Antrenament(cod, tip, descriere, pret)
        try:
            self.__srv_antrenamente.add(antrenament)
            print("Antrenamentul a fost adaugat cu succes!")
        except Exception as e:
            print(e)

    def __remove_antrenament(self):
        cod = self.citire_int("Cod: ")
        try:
            self.__srv_antrenamente.remove(cod)
            print("Antrenamentul a fost sters cu succes!")
        except Exception as e:
            print(e)

    def __find_antrenament(self):
        cod = self.citire_int("Cod: ")
        try:
            antr = self.__srv_antrenamente.find_by_cod(cod)
            print(antr)
        except Exception as e:
            print(e)

    def __update_antrenament(self):
        cod = self.citire_int("Cod: ")
        antrenament = Antrenament(cod, input("Tip: "), input("Descriere: "), self.citire_int("Pret per sesiune: "))
        try:
            self.__srv_antrenamente.update(cod, antrenament)
            print("Antrenamentul a fost modificat cu succes!")
        except Exception as e:
            print(e)

    def run(self):
        while True:
            self.print_main_menu()
            command = self.citire_int("Introduceti o comanda: ")
            match command:
                case 1:
                    self.__add_antrenament()
                case 2:
                    self.__remove_antrenament()
                case 3:
                    self.__find_antrenament()
                case 4:
                    self.__update_antrenament()
                case 5:
                    lista = self.__srv_antrenamente.get_all()
                    for antr in lista:
                        print(antr)
                case 6:
                    lista = self.__srv_antrenamente.find_by_tip(input("Tip: "))
                    for antr in lista:
                        print(antr)
                case 7:
                    cod = self.citire_int("Cod: ")
                    nr_sesiuni = self.citire_int("Numar sesiuni: ")
                    antrenament, pret = self.__srv_antrenamente.rezervare(cod, nr_sesiuni)
                    print(f"{nr_sesiuni} antrenamente au fost rezervate pentru costul total de {pret}!")
                    print(f"Detaliile antrenamentului: {antrenament}")
                case 0:
                    break
                case _:
                    print("Comanda invalida!")