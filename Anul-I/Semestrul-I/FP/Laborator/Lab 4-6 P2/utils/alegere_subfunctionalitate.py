from ui.meniuri import *
from ui.input import *
from domain.functionalitati import *
from utils.validare_input import *

def func1(lista_concurenti: list, istoric_liste: list):
    istoric_liste.append(copiere(lista_concurenti))
    print_menu_adaugare_scor()
    command_adaugare = get_command()
    match command_adaugare:
        case 1:
            adaugare_scor_ultim(lista_concurenti, get_input_nr_proba(), get_input_scor())
        case 2:
            inserare_scor(lista_concurenti, get_input_id_concurent(len(lista_concurenti)), get_input_nr_proba(), get_input_scor())
        case _:
            print("Introduceti o comanda valida!")

def func2(lista_concurenti: list, istoric_liste: list):
    istoric_liste.append(copiere(lista_concurenti))
    print_menu_modificare_scor()
    command_modificare = get_command()
    match command_modificare:
        case 1:
            sterge_scor(lista_concurenti, get_input_id_concurent(len(lista_concurenti)), get_input_nr_proba())
        case 2:
            interval_start, interval_end = get_input_interval(len(lista_concurenti))
            sterge_scor_interval(lista_concurenti, interval_start, interval_end, get_input_nr_proba())
        case 3:
            inlocuire_scor(lista_concurenti, get_input_id_concurent(len(lista_concurenti)), get_input_nr_proba(),
                           get_input_scor())
        case _:
            print("Introduceti o comanda valida!")

def func3(lista_concurenti: list, istoric_liste: list):
    istoric_liste.append(copiere(lista_concurenti))
    print_menu_tiparire()
    command_tiparire = get_command()
    match command_tiparire:
        case 1:
            print(lista_scor_mai_mic(lista_concurenti, get_input_scor_total()))
        case 2:
            print(ordonare_scor(lista_concurenti))
        case 3:
            print(lista_scor_mai_mare_ordonat(lista_concurenti, get_input_scor_total()))
        case 4:
            print_all(lista_concurenti)
        case _:
            print("Introduceti o comanda valida!")

def func4(lista_concurenti: list, istoric_liste: list):
    istoric_liste.append(copiere(lista_concurenti))
    print_menu_operatii()
    command_operatii = get_command()
    match command_operatii:
        case 1:
            interval_start, interval_end = get_input_interval(len(lista_concurenti))
            print(calcul_medie_interval(lista_concurenti, interval_start, interval_end))
        case 2:
            interval_start, interval_end = get_input_interval(len(lista_concurenti))
            id_concurent_scor_minim, scor_minim = calcul_scor_minim(lista_concurenti, interval_start, interval_end)
            print_scor_minim(id_concurent_scor_minim, scor_minim)
        case 3:
            interval_start, interval_end = get_input_interval(len(lista_concurenti))
            print(scor_multiplu10_interval(lista_concurenti, interval_start, interval_end))

def func5(lista_concurenti: list, istoric_liste: list):
    print_menu_filtrare()
    istoric_liste.append(copiere(lista_concurenti))
    command_filtrare = get_command()
    match command_filtrare:
        case 1:
            print(filtrare_multiplu_nr_dat(lista_concurenti, get_input_divizor()))
        case 2:
            print(filtrare_scor_mai_mic(lista_concurenti, get_input_scor_total()))

def func6(lista_concurenti: list, istoric_liste: list):
    if len(istoric_liste) == 0:
        print("Nu exista pasi anteriori!")
    else:
        undo(lista_concurenti, istoric_liste)

def interpreteaza_comenzi(input_line: str, lista_concurenti: list, istoric_liste: list):
    lista_comenzi = [c.strip() for c in input_line.split(";") if c.strip()]
    for comanda in lista_comenzi:
        parti = comanda.split()
        if not parti:
            continue
        operatie = parti[0]
        match operatie:
            case "add":
                if len(parti) != 3:
                    print("Parametrii invalizi!")
                elif not validare_nr_proba(parti[2]):
                    print("Numar proba invalid!")
                elif not validare_scor(parti[1]):
                    print("Scor invalid!")
                else:
                    istoric_liste.append(copiere(lista_concurenti))
                    adaugare_scor_ultim(lista_concurenti, int(parti[2]), int(parti[1]))
            case "delete":
                if len(parti) != 3:
                    print("Parametrii invalizi!")
                elif not validare_nr_proba(parti[2]):
                    print("Numar proba invalid!")
                elif not validare_id_concurent(parti[1], len(lista_concurenti)):
                    print("ID participant invalid!")
                else:
                    istoric_liste.append(copiere(lista_concurenti))
                    sterge_scor(lista_concurenti, int(parti[1]), int(parti[2]))
            case "print":
                print_all(lista_concurenti)
            case "undo":
                func6(lista_concurenti, istoric_liste)
            case "help":
                print_help()
            case _:
                print("Comanda invalida!")