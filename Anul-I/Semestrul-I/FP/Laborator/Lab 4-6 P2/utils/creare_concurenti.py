def creare_concurent(id_concurent: int) -> dict:
    """
    Creeaza un concurent cu numarul de ordine furnizat
    :param id_concurent - numarul de ordine al concurentului
    output - returneaza un dictionar ce contine id-ul concurentului si scorurile sale
    """
    return {'id_concurent': id_concurent, 'scoruri': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]}

def adaugare_concurenti(nr_concurenti: int, lista_concurenti: list) -> None:
    """
    Adauga toti concurentii in lista
    :param nr_concurenti - numarul de concurenti inregistrati
    :param lista_concurenti - lista in care sunt retinuti concurentii
    """
    for id_concurent in range(nr_concurenti):
        lista_concurenti.append(creare_concurent(id_concurent + 1))
