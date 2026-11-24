from utils.creare_concurenti import *

# F1

def adaugare_scor_ultim(lista_concurenti: list, nr_proba: int, scor: int) -> None:
    """
    Adauga un scor (>= 1, <= 10) ultimului participant la o proba (>= 1, <= 10)
    :param lista_concurenti - lista concurentilor
    :param nr_proba - numarul probei
    :param scor - scorul
    """
    lista_concurenti.append(creare_concurent(len(lista_concurenti) + 1))
    lista_concurenti[-1]['scoruri'][nr_proba - 1] = scor

def inserare_scor(lista_concurenti: list, id_concurent: int, nr_proba: int, scor: int) -> None:
    """
    Insereaza un scor (>= 1, <= 10) unui participant la o proba (>= 1, <= 10)
    :param lista_concurenti: lista concurentilor
    :param id_concurent: ID-ul participantului
    :param nr_proba: numarul probei
    :param scor: scorul
    """
    if lista_concurenti[id_concurent - 1]['scoruri'][nr_proba - 1] != 0:
        print("Scor deja existent!")
    else:
        lista_concurenti[id_concurent - 1]['scoruri'][nr_proba - 1] = scor

#F2

def sterge_scor(lista_concurenti: list, id_concurent: int, nr_proba: int) -> None:
    """
    Sterge scorul unui participant dat la proba mentionata
    :param lista_concurenti: lista concurentilor
    :param id_concurent: ID-ul participantului
    :param nr_proba: numarul probei
    """
    if lista_concurenti[id_concurent - 1]['scoruri'][nr_proba - 1] == 0:
        print("Scorul este deja nul!")
    else:
        lista_concurenti[id_concurent - 1]['scoruri'][nr_proba - 1] = 0

def sterge_scor_interval(lista_concurenti: list, interval_start: int, interval_end: int, nr_proba: int) -> None:
    """
    Sterge scorul unui interval de participanti la o proba data
    :param lista_concurenti: lista concurentilor
    :param interval_start: primul participant din intervalul de participanti
    :param interval_end: ultimul participant din intervalul de participanti
    :param nr_proba: numarul probei
    """
    for concurent in lista_concurenti[interval_start - 1:interval_end]:
        concurent['scoruri'][nr_proba - 1] = 0

def inlocuire_scor(lista_concurenti: list, id_concurent: int, nr_proba: int, scor: int) -> None:
    """
    Inlocuieste scorul unui participant dat la proba ceruta
    :param lista_concurenti: Lista concurentilor
    :param id_concurent: ID-ul participantului
    :param nr_proba: Numarul probei
    :param scor: Scorul
    """
    if lista_concurenti[id_concurent - 1]['scoruri'][nr_proba - 1] == 0:
        print("Scorul este nul!")
    else:
        lista_concurenti[id_concurent - 1]['scoruri'][nr_proba - 1] = scor

# F3

def suma_scor_concurent(concurent: dict) -> int:
    """
    Returneaza suma scorurilor obtinute de catre un participant
    :param concurent: dictionar ce contine datele unui concurent (ID, scoruri)
    :return: Suma scorurilor concurentului
    """
    return sum(concurent['scoruri'])

def lista_scor_mai_mic(lista_concurenti: list, scor_total: int) -> list:
    """
    Returneaza participantii cu scorul total mai mic decat cel dat
    :param lista_concurenti: lista concurentilor
    :param scor_total: scorul total cerut
    :return lista_result: lista cu participantii cu scorul mai mic decat cel dat
    """
    lista_result = []
    for concurent in lista_concurenti:
        if suma_scor_concurent(concurent) < scor_total:
            lista_result.append(concurent)

    return lista_result

def ordonare_scor(lista_concurenti: list) -> list:
    """
    Sorteaza si tipareste participantii in ordinea crescatoare a scorurilor totale obtinute
    :param lista_concurenti: lista concurentilor
    :return lista_ordonata: lista cu participantii in ordine crescatoare a scorurilor totale
    """
    lista_ordonata = lista_concurenti.copy()
    lista_ordonata.sort(key=suma_scor_concurent)

    return lista_ordonata

def lista_scor_mai_mare_ordonat(lista_concurenti: list, scor_total: int) -> list:
    """
    Returneaza o lista cu participantii cu scorul total mai mare decat cel dat in ordine crescatoare
    :param lista_concurenti:
    :param scor_total:
    :return: lista_ordonata: lista cu participantii cu scorul mai mare decat cel dat, ordonata crescator
    """
    lista_ordonata = []
    for concurent in lista_concurenti:
        if suma_scor_concurent(concurent) > scor_total:
            lista_ordonata.append(concurent)

    lista_ordonata.sort(key=suma_scor_concurent)
    return lista_ordonata

# F4

def calcul_medie_interval(lista_concurenti: list,interval_start: int, interval_end: int) -> float:
    """
    Calculeaza medie scorurilor totale ale unui interval de participanti
    :param lista_concurenti: lista concurentilor
    :param interval_start:
    :param interval_end:
    :return: medie_scoruri: media scorurilor totale ale intervalului de participanti
    """
    medie_scoruri = 0
    for id_concurent in range(interval_start - 1, interval_end):
        medie_scoruri += suma_scor_concurent(lista_concurenti[id_concurent])

    medie_scoruri /= (interval_end - interval_start + 1)
    return medie_scoruri

def calcul_scor_minim(lista_concurenti: list, interval_start: int, interval_end: int) -> tuple:
    """
    Cacluleaza scorul minim dintr un interval de participanti
    :param lista_concurenti: lista concurentilor
    :param interval_start: inceputul intervalului de participanti
    :param interval_end: sfarsitul intervalului de participanti
    :return: id_concurent_scor_minim, scor_minim: id-ul concurentului cu scorul minim si scorul sau
    """
    scor_minim = 101
    id_concurent_scor_minim = 0
    for concurent in lista_concurenti[interval_start - 1:interval_end]:
        if suma_scor_concurent(concurent) < scor_minim:
            scor_minim = suma_scor_concurent(concurent)
            id_concurent_scor_minim = concurent['id_concurent']

    return id_concurent_scor_minim, scor_minim

def scor_multiplu10_interval(lista_concurenti: list, interval_start: int, interval_end: int) -> list:
    """
    Returneaza lista cu participantii din intervalul dat care au scorul divizibil cu 10 si nenul
    :param lista_concurenti: lista concurentilor
    :param interval_start: inceputul intervalului de participanti
    :param interval_end: sfarsitul intervalului de participanti
    :return lista_filtrata: lista concurentilor ce au scorul divizibil cu 10
    """
    lista_filtrata = []
    for concurent in lista_concurenti[interval_start - 1:interval_end]:
            if suma_scor_concurent(concurent) % 10 == 0 and suma_scor_concurent(concurent) != 0:
                lista_filtrata.append(concurent)

    return lista_filtrata

# F5

def filtrare_multiplu_nr_dat(lista_concurenti: list, numar: int) -> list:
    """
    Returneaza lista cu participantii care au scorul divizibil cu un numar dat si nenul
    :param lista_concurenti: lista participantilor
    :param numar: numarul dat, un numar natural nenul
    :return: lista_filtrata - lista cu participanti care au scorul divizibil cu numarul dat si nenul
    """
    lista_filtrata = []
    for concurent in lista_concurenti:
        if suma_scor_concurent(concurent) % numar == 0 and suma_scor_concurent(concurent) != 0:
            lista_filtrata.append(concurent)

    return lista_filtrata

def filtrare_scor_mai_mic(lista_concurenti: list, scor_total: int) -> list:
    """
    Returneaza participantii cu scorul total mai mic decat cel dat
    :param lista_concurenti: lista concurentilor
    :param scor_total: scorul total cerut
    :return lista_filtrata: lista cu participantii cu scorul mai mic decat cel dat
    """
    lista_filtrata = []
    for concurent in lista_concurenti:
        if suma_scor_concurent(concurent) < scor_total:
            lista_filtrata.append(concurent)

    return lista_filtrata

# F6

def copiere(lista_concurenti: list) -> list:
    """
    Creeaza o copie a listei de concurenti
    :param lista_concurenti: lista concurentilor
    :return copie: o copie a listei de concurenti
    """
    copie = []
    for concurent in lista_concurenti:
        copie_concurent = {'id_concurent': concurent['id_concurent'], 'scoruri': concurent['scoruri'].copy()}
        copie.append(copie_concurent)

    return copie

def undo(lista_concurenti: list, istoric_liste: list) -> None:
    """
    Readuce lista de concurenti la starea anterioara
    :param lista_concurenti: lista concurentilor
    :param istoric_liste: istoricul starilor anterioare ale listei de concurenti
    """
    stare_anterioara = istoric_liste.pop()
    lista_concurenti[:] = stare_anterioara