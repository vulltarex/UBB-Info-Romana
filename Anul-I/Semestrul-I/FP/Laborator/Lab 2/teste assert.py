def functie():
    """
    <ce face functia>
    input: <date de intrare: tip si scop>
    output: <date de iesire>
    raises: cand se arunca exceptia si de ce
    """
    pass # {}

def suma(l):
    """
    calculeaza suma numerelor intregi din l
    input: l - lista de numere intregi
    output: s - intreg, suma numerelor din l
    """
    s = 0
    for e in l:
        s += e
    return s

def test_suma():
    if suma([1, 2, 3]) != 6:
        print("Nu merge!")

def citeste_vector():
    """
    citeste de la tastatura o lista de numere intregi pana cand se introduce "STOP"
    input: -
    output: numere - o lista de numere intregi
    """
    i = 0
    numere = []
    while True:
        numar = input(f"Da numarul {i}: ")
        if numar == "STOP":
            break
        try:
            numar = int(numar)
        except ValueError:
            continue
        numar = int(numar)
        numere.append(numar)
        i += 1
    return numere

def main():
    numere = []
    while True:
        comanda = int(input("Da comanda: "))
        if comanda == 1:
            citeste_vector() # citeste de la tastatura vector
        elif comanda == 2: # else if
            s = suma(numere) # afiseaza suma elem din vector
            print(f"Suma este: {s}")
        elif comanda == 4:
            break

main()
