from domain.functionalitati import *

def test_creare_concurent():
    concurent = creare_concurent(1)
    assert concurent['id_concurent'] == 1
    assert concurent['scoruri'] == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert len(concurent['scoruri']) == 10

    concurent2 = creare_concurent(5)
    assert concurent2['id_concurent'] == 5

def test_adaugare_concurenti():
    lista = []
    adaugare_concurenti(3, lista)
    assert len(lista) == 3
    assert lista[0]['id_concurent'] == 1
    assert lista[1]['id_concurent'] == 2
    assert lista[2]['id_concurent'] == 3

    lista2 = []
    adaugare_concurenti(0, lista2)
    assert len(lista2) == 0

def test_adaugare_scor_ultim():
    lista = []
    adaugare_concurenti(5, lista)
    nr_proba = 1
    scor = 5
    adaugare_scor_ultim(lista, nr_proba, scor)
    assert lista[5]['scoruri'][0] == 5
    assert len(lista) == 6

def test_inserare_scor():
    lista = []
    adaugare_concurenti(5, lista)
    concurent = 2
    proba = 1
    scor = 5
    inserare_scor(lista, concurent, proba, scor)
    assert lista[1]['scoruri'][0] == 5

def test_sterge_scor():
    lista = []
    adaugare_concurenti(5, lista)
    concurent = 2
    proba = 1
    inserare_scor(lista, concurent, proba, 5)
    sterge_scor(lista, concurent, proba)
    assert lista[1]['scoruri'][0] == 0

def test_sterge_scor_interval():
    lista = []
    adaugare_concurenti(5, lista)
    interval_start = 1
    interval_end = 3
    nr_proba = 1
    lista[0]['scoruri'][0] = 3
    lista[1]['scoruri'][0] = 6
    lista[2]['scoruri'][0] = 1
    lista[3]['scoruri'][0] = 5
    lista[4]['scoruri'][0] = 9
    sterge_scor_interval(lista, interval_start, interval_end, nr_proba)

    assert lista[0]['scoruri'][0] == 0
    assert lista[1]['scoruri'][0] == 0
    assert lista[2]['scoruri'][0] == 0
    assert lista[3]['scoruri'][0] == 5
    assert lista[4]['scoruri'][0] == 9

def test_inlocuire_scor():
    lista = []
    adaugare_concurenti(5, lista)
    lista[1]['scoruri'][0] = 3
    concurent = 2
    proba = 1
    scor = 5
    inlocuire_scor(lista, concurent, proba, scor)
    assert lista[1]['scoruri'][0] == 5

def test_suma_scor_concurent():
    concurent1 = {'id_concurent': 1, 'scoruri': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]}
    assert suma_scor_concurent(concurent1) == 0

    concurent2 = {'id_concurent': 2, 'scoruri': [5, 7, 8, 6, 9, 10, 4, 3, 2, 1]}
    assert suma_scor_concurent(concurent2) == 55

    concurent3 = {'id_concurent': 3, 'scoruri': [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]}
    assert suma_scor_concurent(concurent3) == 100

def test_lista_scor_mai_mic():
    scor_total = 75
    lista_concurenti = []
    adaugare_concurenti(5, lista_concurenti)
    lista_concurenti[0]['scoruri'] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # 55
    lista_concurenti[1]['scoruri'] = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]  # 100
    lista_concurenti[2]['scoruri'] = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]  # 80
    lista_concurenti[3]['scoruri'] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 0
    lista_concurenti[4]['scoruri'] = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  # 10
    lista_test = lista_scor_mai_mic(lista_concurenti, scor_total)

    assert lista_test == [{'id_concurent': 1, 'scoruri': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]},
                          {'id_concurent': 4, 'scoruri': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]},
                          {'id_concurent': 5, 'scoruri': [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]}]

def test_ordonare():
    lista = [
        {'id_concurent': 1, 'scoruri': [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]},  # 50
        {'id_concurent': 2, 'scoruri': [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]},  # 100
        {'id_concurent': 3, 'scoruri': [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]},  # 10
    ]

    lista_sortata = ordonare_scor(lista)
    assert lista_sortata[0]['id_concurent'] == 3
    assert lista_sortata[1]['id_concurent'] == 1
    assert lista_sortata[2]['id_concurent'] == 2

def test_lista_scor_mai_mare_ordonat():
    lista = [
        {'id_concurent': 1, 'scoruri': [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]}, # 50
        {'id_concurent': 2, 'scoruri': [3, 3, 3, 3, 3, 3, 3, 3, 3, 3]}, # 30
        {'id_concurent': 3, 'scoruri': [4, 4, 4, 4, 4, 4, 4, 4, 4, 4]}, # 40
    ]

    assert lista_scor_mai_mare_ordonat(lista, 30) == [
        {'id_concurent': 3, 'scoruri': [4, 4, 4, 4, 4, 4, 4, 4, 4, 4]},
        {'id_concurent': 1, 'scoruri': [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]}
    ]

def test_calcul_medie_interval():
    lista_concurenti = []
    adaugare_concurenti(5, lista_concurenti)
    lista_concurenti[0]['scoruri'] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # 55
    lista_concurenti[1]['scoruri'] = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]  # 100
    lista_concurenti[2]['scoruri'] = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]  # 80
    lista_concurenti[3]['scoruri'] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 0
    lista_concurenti[4]['scoruri'] = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  # 10

    assert calcul_medie_interval(lista_concurenti, 2, 4) == 60

def test_calcul_scor_minim():
    lista_concurenti = []
    adaugare_concurenti(5, lista_concurenti)
    lista_concurenti[0]['scoruri'] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # 55
    lista_concurenti[1]['scoruri'] = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]  # 100
    lista_concurenti[2]['scoruri'] = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]  # 80
    lista_concurenti[3]['scoruri'] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 0
    lista_concurenti[4]['scoruri'] = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  # 10

    id_concurent_scor_minim, scor_minim = calcul_scor_minim(lista_concurenti, 2, 4)
    assert id_concurent_scor_minim == 4
    assert scor_minim == 0

def test_scor_multiplu10_interval():
    lista_concurenti = []
    adaugare_concurenti(5, lista_concurenti)
    lista_concurenti[0]['scoruri'] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # 55
    lista_concurenti[1]['scoruri'] = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]  # 100
    lista_concurenti[2]['scoruri'] = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]  # 80
    lista_concurenti[3]['scoruri'] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 0
    lista_concurenti[4]['scoruri'] = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  # 10

    assert scor_multiplu10_interval(lista_concurenti, 2, 4) == [
        {'id_concurent': 2, 'scoruri': [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]},
        {'id_concurent': 3, 'scoruri': [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]}
    ]

def test_filtrare_multiplu_nr_dat():
    lista = [
        {'id_concurent': 1, 'scoruri': [1, 2, 3, 4, 4, 6, 7, 8, 9, 10]},  # 54
        {'id_concurent': 2, 'scoruri': [1, 2, 3, 4, 0, 6, 7, 8, 9, 10]},  # 50
        {'id_concurent': 3, 'scoruri': [10, 10, 10, 10, 10, 10, 10, 10, 10, 9]},  # 99
        {'id_concurent': 4, 'scoruri': [1, 2, 3, 4, 0, 0, 0, 0, 0, 0]}  # 10
    ]

    assert filtrare_multiplu_nr_dat(lista, 3) == [{'id_concurent': 1, 'scoruri': [1, 2, 3, 4, 4, 6, 7, 8, 9, 10]},
                                          {'id_concurent': 3, 'scoruri': [10, 10, 10, 10, 10, 10, 10, 10, 10, 9]}]

def test_filtrare_scor_mai_mic():
    lista_concurenti = []
    adaugare_concurenti(5, lista_concurenti)
    lista_concurenti[0]['scoruri'] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # 55
    lista_concurenti[1]['scoruri'] = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]  # 100
    lista_concurenti[2]['scoruri'] = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]  # 80
    lista_concurenti[3]['scoruri'] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 0
    lista_concurenti[4]['scoruri'] = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  # 10

    assert filtrare_scor_mai_mic(lista_concurenti, 55) == [
        {'id_concurent': 4, 'scoruri': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]},
        {'id_concurent': 5, 'scoruri': [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]}
    ]

def test_copie():
    lista = []
    adaugare_concurenti(5, lista)
    lista[0]['scoruri'] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # 55
    lista[1]['scoruri'] = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]  # 100
    lista[2]['scoruri'] = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]  # 80
    lista[3]['scoruri'] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 0
    lista[4]['scoruri'] = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]  # 10

    lista_copie = copiere(lista)
    assert lista_copie == lista
    assert lista_copie is not lista
    assert lista_copie[0] is not lista[0]
    assert lista_copie[0]['scoruri'] is not lista[0]['scoruri']
    assert lista_copie[0]['scoruri'] == lista[0]['scoruri']
    assert lista_copie[0]['scoruri'][0] == lista[0]['scoruri'][0]
    assert len(lista_copie) == len(lista)

def test_all():
    test_creare_concurent()
    test_adaugare_concurenti()
    test_suma_scor_concurent()
    test_inserare_scor()
    test_sterge_scor()
    test_sterge_scor_interval()
    test_inlocuire_scor()
    test_lista_scor_mai_mic()
    test_ordonare()
    test_filtrare_multiplu_nr_dat()
    test_adaugare_scor_ultim()
    test_lista_scor_mai_mare_ordonat()
    test_calcul_medie_interval()
    test_calcul_scor_minim()
    test_scor_multiplu10_interval()
    test_filtrare_scor_mai_mic()
    test_copie()