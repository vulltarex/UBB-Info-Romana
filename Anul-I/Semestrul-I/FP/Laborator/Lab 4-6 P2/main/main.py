from utils.alegere_subfunctionalitate import *
from teste.asertiuni import *

def main():
    lista_concurenti = [creare_concurent(1)]
    istoric_liste = []
    while True:
        print_alegere_ui()
        command_ui = get_command()
        match command_ui:
            case 1:
                print_menu()
                command = get_command()
                match command:
                    case 1:
                        func1(lista_concurenti, istoric_liste)
                    case 2:
                        func2(lista_concurenti, istoric_liste)
                    case 3:
                        func3(lista_concurenti, istoric_liste)
                    case 4:
                        func4(lista_concurenti, istoric_liste)
                    case 5:
                        func5(lista_concurenti, istoric_liste)
                    case 6:
                        func6(lista_concurenti, istoric_liste)
                    case 7:
                        break
                    case _:
                        print("Introduceti o comanda valida!")
            case 2:
                interpreteaza_comenzi(get_command_func(), lista_concurenti, istoric_liste)
            case _:
                print("Introduceti o comanda valida!")

test_all()