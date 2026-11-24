from math import factorial
from random import sample
from math import perm, comb
from itertools import permutations, combinations
from itertools import combinations_with_replacement

def aranjamente(cuvant, k, numar_total = False, aleator = False):
    if numar_total:
        return perm(len(cuvant),k)
    elif aleator:
        return sample(cuvant, k)
    else:
        lista = list(permutations(cuvant, k))
        return lista

def combinari(cuvant, k, numar_total = False, aleator = False):
    if numar_total:
        return comb(len(cuvant),k)
    elif aleator:
        return sample(cuvant, k)
    else:
        lista = list(combinations(cuvant, k))
        return lista

for p in permutations("randomise"):
    print(p)

nr_permutari = factorial(len("randomise"))
print(nr_permutari)

permutare_aleatoare = sample("randomise", len("randomise"))
print(permutare_aleatoare)

print("aranjamente:")
print(aranjamente("word", 2))
print(aranjamente("word", 2, numar_total=True))
print(aranjamente("word", 2, aleator=True))

list_comb = list(combinations("word", 2))
print("combinari:")
print(combinari("word", 2))
print(combinari("word", 2, numar_total=True))
print(combinari("word", 2, aleator=True))

sortimente = ['A', 'C', 'F', 'K', 'M', 'V', 'Z']

rezultat = list(combinations_with_replacement(sortimente, 3))

print("Sortimente inghetata:")

for r in rezultat:
    print(r)

print(len(rezultat))