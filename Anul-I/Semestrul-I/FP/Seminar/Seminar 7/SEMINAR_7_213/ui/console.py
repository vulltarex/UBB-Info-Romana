from colorama import Fore


class Console:
    def __init__(self, service):
        self.__srv = service

    @staticmethod
    def print_menu():
        print("1. Adauga melodie")
        print("2. Sterge melodie dupa id")
        print("3. Cauta melodii cu durata intre doua valori")
        print("4. Modifica melodie")
        print("--" * 10)
        print("P. Afiseaza toate melodiile")
        print("E. Exit")

    @staticmethod
    def __print_melodii(lista_melodii):
        if not lista_melodii:
            print("Nu exista melodii in lista.")
        else:
            print(Fore.MAGENTA + "Lista de melodii:" + Fore.RESET)
            for melodie in lista_melodii:
                print(melodie)

    def __add_ui(self):
        m_id = input("ID melodie:")
        titlu = input("Titlu: ")
        artist = input("Artist: ")
        gen = input("Gen:")
        durata = input("Durata")

        try:
            m_id = int(m_id)
            durata = float(durata)
            self.__srv.add_melodie(m_id, titlu, artist, gen, durata)
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)
        else:
            print(Fore.GREEN + "Melodia a fost adaugata cu succes." + Fore.RESET)

    def __delete_ui(self):
        m_id = input("ID-ul melodiei de sters")
        try:
            m_id = int(m_id)
            melodie_stearsa = self.__srv.delete_melodie(m_id)
            print(f"{melodie_stearsa} a fost stearsa.")
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)

    def __filter_by_durata_ui(self):
        durata_lower_bound = input("Durata melodiilor ar trebui sa fie mai mare de: ")
        durata_upper_bound = input("Durata melodiilor ar trebui sa fie mai mica de: ")
        try:
            durata_upper_bound = float(durata_upper_bound)
            durata_lower_bound = float(durata_lower_bound)
            melodii_filtered = self.__srv.filter_by_durata(durata_lower_bound, durata_upper_bound)
            print(f"Melodiile cu durata mai mare de {durata_lower_bound} si mai mica de {durata_upper_bound} sunt:")
            Console.__print_melodii(melodii_filtered)
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)

    def __modify_ui(self):
        m_id = input("ID melodie:")
        titlu = input("Titlu: ")
        artist = input("Artist: ")
        gen = input("Gen:")
        durata = input("Durata")
        try:
            m_id = int(m_id)
            durata = float(durata)
            melodie_veche = self.__srv.update_melodie(m_id, titlu, artist, gen, durata)
            print(f"{melodie_veche} a fost actualizata.")
        except ValueError as e:
            print(Fore.RED + str(e) + Fore.RESET)

    def run(self):
        while True:
            Console.print_menu()
            option = input(">>>").strip()
            if option == "1":
                self.__add_ui()
            elif option == "2":
                self.__delete_ui()
            elif option == "3":
                self.__filter_by_durata_ui()
            elif option == '4':
                self.__modify_ui()
            elif option.upper() == 'P':
                Console.__print_melodii(self.__srv.get_melodii())
            elif option.upper() == 'E':
                break
