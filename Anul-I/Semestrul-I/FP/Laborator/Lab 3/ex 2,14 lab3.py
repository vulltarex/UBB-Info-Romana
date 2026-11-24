def citire_lista():
    """
    Se citeste o lista de numere intregi pana se introduce "STOP"
    input: -
    output: lista - o lista de numere intregi
    raises: ValueError - daca se introduce o valoare diferita de un nr intreg
    """
    lista = []
    i = 0
    while True:
        nr = input(f"Numarul {i}: ")
        if nr == "STOP":
            break
        try:
            nr = int(nr)
        except ValueError:
            print("Nu este un numar!")
            continue
        lista.append(nr)
        i += 1
    return lista

def nr_valori_distincte(lista):
    """
    Se returneaza numarul de valori distincte dintr-o lista
    input: lista - o lista de numere intregi
    output: cnt - numarul de valori distincte din lista
    """
    cnt = 0
    aparitii = [] #se stocheaza nr aparute in lista data prin parametru
    for valoare in lista:
        if valoare not in aparitii:
            cnt += 1
            aparitii.append(valoare)
    return cnt

def secv_max_3val_dist(lista):
    """
    Determina cea mai lunga secventa din lista ce contine maxim 3 valori
    distincte
    input: lista - o lista de numere intregi
    output: o subsecventa din lista furnizata ce respecta conditia ceruta
    """
    
    index_left_current = 0  # indici stanga si dreapta pentru verificarea subsecv
    index_right_current = 0
    len_current = 1 #   lungimea secventei verificate

    index_left_max = 0 # indicii stanga si dreapta ai subsecventei de lungime maxima
    index_right_max = 0
    len_max = 1 # lungimea subsecventei cautate
    
    while index_right_current <= len(lista) - 1:
        
        if nr_valori_distincte(lista[index_left_current:index_right_current]) <= 3 and len_current > len_max:
            index_left_max = index_left_current
            index_right_max = index_right_current
            len_max = len_current
            
        if nr_valori_distincte(lista[index_left_current:index_right_current]) <= 3:
            index_right_current += 1
            len_current += 1
            
        else:
            index_left_current += 1
            len_current -= 1
    
    if nr_valori_distincte(lista[index_left_current:index_right_current]) <= 3 and len_current > len_max:
        index_left_max = index_left_current
        index_right_max = index_right_current
        
    return lista[index_left_max:index_right_max]

def nr_cifre_comune(nr1, nr2):
    """
    Determina numarul cifre distincte comune a doua numere intregi
    input: nr1, nr2 - doua numere intregi
    output: cnt - numarul de cifre distincte comune
    """
    nr1 = abs(nr1)
    nr2 = abs(nr2)
    cnt = 0
    cifre = []
    while nr1 != 0:
        if nr1 % 10 not in cifre:
            cifre.append(nr1 % 10)
        nr1 //= 10
    while nr2 != 0:
        if nr2 % 10 in cifre:
            cifre.remove(nr2 % 10)
            cnt += 1
        nr2 //= 10
    return cnt

def verif_2cif_comune_lista(lista):
    """
    Verifica daca toate elementele dintr-o lista au cel putin doua cifre distincte comune
    input: lista - o lista de numere intregi
    output: 0 daca lista nu respecta conditia, 1 altfel
    """
    for index in range(len(lista) - 1):
        if nr_cifre_comune(lista[index], lista[index + 1]) < 2:
            return 0
    return 1

def secv_max_2val_consecutive_2cif_comune(lista):
    """
    Determina cea mai lunga secventa din lista in care oricare doua elem. consecutive
    au minim 2 cifre distincte comune
    input: lista - o lista de numere intregi
    output: o secventa din lista furnizata ce respecta conditia ceruta
    """
    
    if len(lista) < 2:
        return []
    else:
    
        index = 0 # indicele de inceput al secventei verificate
        length = 1 # lungimea secventei verificate

        index_secv = 0 # indicele de inceput al secventei cautate
        length_secv = 0 # lungimea secventei cautate

        while index + length - 1 <= len(lista) - 1:
            
            if verif_2cif_comune_lista(lista[index:index + length]) == 1 and length > length_secv:
                length_secv = length
                index_secv = index

            if verif_2cif_comune_lista(lista[index:index + length]) == 1:
                length += 1
            else:
                index += 1
                length -= 1

        if verif_2cif_comune_lista(lista[index:index + length]) == 1 and length > length_secv:
                length_secv = length
                index_secv = index

        return lista[index_secv:index_secv + length_secv]

def suma_elem(lista):
    """
    Determina suma elementelor unei liste
    input: lista - o lista de numere intregi
    output: suma - suma tuturor valorilor din lista
    """
    suma = 0
    for element in lista:
        suma += element
    return suma

def secv_max_sum5(lista):
    """
    Determina cea mai lunga secventa dintr-o lista de numere intregi care sa aiba suma elementelor
    egala cu 5
    input: lista - o lista de numere intregi
    output: o subsecventa a listei ce respecta conditia ceruta
    """
    index = 0
    length = 1
    ok = 0

    index_secv = 0
    length_secv = 0

    while index + length - 1 <= len(lista) - 1:
            
        if suma_elem(lista[index:index + length]) == 5 and length > length_secv:
            length_secv = length
            index_secv = index
            ok = 1

        if suma_elem(lista[index:index + length]) <= 5:
            length += 1
        else:
            index += 1
            length -= 1
            
    if suma_elem(lista[index:index + length]) == 5 and length > length_secv:
        length_secv = length
        index_secv = index
        ok = 1

    if ok == 1:
        return lista[index_secv:index_secv + length_secv]
    else:
        print ("Nu exista!")
        return []

def testari():
    assert secv_max_3val_dist([1, 1, 2, 2, 2, 3]) == [1, 1, 2, 2, 2, 3]
    assert secv_max_3val_dist([1, 2]) == [1, 2]
    assert secv_max_3val_dist([1, 2, 3, 4, 4, 3, 2, 2, 2, 5, 5, 5]) == [2, 3, 4, 4, 3, 2, 2, 2]

    assert secv_max_2val_consecutive_2cif_comune([123]) == []
    assert secv_max_2val_consecutive_2cif_comune([12, 123, 234, 1, 112, 321, 1]) == [12, 123, 234]
    assert secv_max_2val_consecutive_2cif_comune([12, 12, 12, 12, 12]) == [12, 12, 12, 12, 12]

    assert secv_max_sum5([1, 1, 2, 1, 5, 1, 1, 1, 1, 0, 1, 0]) == [1, 1, 1, 1, 0, 1, 0]
    assert secv_max_sum5([5]) == [5]

def main():
    lista = []
    while True:
        comanda = int(input("Da o comanda:"))
        if comanda == 1:
            lista = citire_lista()
        elif comanda == 2:
            print(secv_max_3val_dist(lista))
        elif comanda == 3:
            print(secv_max_2val_consecutive_2cif_comune(lista))
        elif comanda == 4:
            print(secv_max_sum5(lista))
        elif comanda == 5:
            break

testari()
main()
