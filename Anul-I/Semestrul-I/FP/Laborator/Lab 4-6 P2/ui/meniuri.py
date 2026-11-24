def print_menu():
    print("""
    1. Adauga un scor la un participant
    2. Modificare scor
    3. Tipareste lista de participanti
    4. Operatii pe subset de participanti
    5. Filtrare
    6. Undo
    7. Incheie executia programului
    """)

def print_menu_adaugare_scor():
    print("""
    1. Adauga scor pentru un nou participant (ultimul participant)
    2. Inserare scor pentru un participant
    """)

def print_menu_modificare_scor():
    print("""
    1. Sterge scorul pentru un participant
    2. Sterge scorul pentru un interval de participanti
    3. Inlocuieste scorul unui participant
    """)

def print_menu_tiparire():
    print("""
    1. Tipareste participantii care au un scor mai mic decat un scor dat
    2. Tipareste participantii ordonat dupa scor
    3. Tipareste participantii cu scor mai mare decat un scor dat, ordonat crescator
    4. Tipareste toti participantii
    """)

def print_menu_operatii():
    print("""
    1. Calculeaza media scorurilor pentru un interval
    2. Calculeaza scorul minim pentru un interval
    3. Tipareste participantii dintr un interval care au scorul multiplu de 10
    """)

def print_menu_filtrare():
    print("""
    1. Filtrare participanti cu scorul divizibil cu un numar nenul dat
    2. Filtrare participanti cu scorul mai mic decat un numar dat
    """)

def print_scor_minim(id_concurent: int, scor_minim: int) -> None:
    print(f"Scorul minim este {scor_minim} la concurentul {id_concurent}")

def print_all(lista_concurenti: list) -> None:
    for concurent in lista_concurenti:
        print(concurent)

def print_alegere_ui() -> None:
    print("""Alege interfata:
          1. Tip meniu
          2. Linie de comanda (pentru ajutor tasteaza "help") 
          """)

def print_help() -> None:
    print("""
    Operatii: 
    
    add - adauga un concurent nou cu scorul precizat la o anumita proba
    Sintaxa: add <scor> <proba>
    
    delete - sterge un scor din lista
    Sintaxa: delete <id_concurent> <proba>
    
    print - tipareste toti participantii si scorurile lor
    Sintaxa: print
    
    undo - anuleaza ultima operatie
    Sintaxa: undo
    """)