def citire():
    n = int(input("Da-mi numarul de elemente: "))
    numere = []
    for i in range(n):
        numar = int(input(f"Da-mi numarul {i + 1}: "))
        numere.append(numar)
    return numere

def calculeaza_suma(numere):
    suma = 0
    for numar in numere:
        suma += numar
    return suma

def afiseaza_suma(suma):
    print(f"Suma este {suma}")

if calculeaza_suma([1, 2, 3, 4, 5]) != 20:
    print("nu merge")

numere = citire()
suma = calculeaza_suma(numere)
afiseaza_suma(suma)
