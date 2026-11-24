from itertools import product
from random import randint, random
from matplotlib.pyplot import plot, grid, xticks, yticks, title, show, axis
from math import dist, pi
# help('itertools.product')
# help('random.randint')

"""
Doi jucatori aleg doua sume distincte care se pot obtine prin aruncarea a trei zaruri, apoi simuleaza
în Python aruncarea a trei zaruri de 100000 de ori. Jucatorul câstigator este cel a carui suma apare
mai des. Ce sume distincte ar trebui sa aleaga cei doi jucatori pentru a-si maximiza sansele de câstig
"""

#generarea tuturor sumelor posibile prin aruncarea a trei zaruri

def prob1():
    sum_counts = {total: 0 for total in range(3, 19)}

    for roll in product (range(1,7), repeat=3):
        sum_counts[sum(roll)] += 1
    plot(sum_counts.keys(), sum_counts.values(), 'ro')
    grid()
    xticks(range(3,19))
    title("Distributie sume")
    show()

    sim_count = {total: 0 for total in range(3,19)}
    for i in range(100000):
        z1 = randint(1,6)
        z2 = randint(1,6)
        z3 = randint(1,6)
        suma = z1 + z2 + z3
        sim_count[suma] += 1

    plot(sim_count.keys(), sim_count.values(), 'ro')
    xticks(range(3,19))
    yticks()
    grid()
    title("Distributie 100k aruncari")
    show()
    # Simulati aruncarea a 3 zaruri de 100.000 ori
    # Valoarea zarului se obtine cu functia randint(a,b) alege random in [a,b]


"""
Fie A un eveniment asociat unui experiment. Repetam experimentul de N ori.
Fie kN(A) -> nr de realizari ale ev. A in cele N simulari
Nr. fN(A) = kN(A)/N se numeste frecv. relativa a ev. A
fN(A) -> (N tinde inf) prob. teoretica
"""
def patrat(nr_pcte=2000, cerinta=3):
    axis('square')
    axis((0, 1, 0, 1))
    count = 0
    A, B, C, D, E = [0, 0], [1, 0], [1, 1], [0, 1], [0.5, 0.5]
    print("Probabilitate teoretica: ")
    match cerinta:
        case 1:
            for _ in range(nr_pcte):
                F = [random(), random()]
                if dist(F, E) < 0.5:
                    count = count + 1
                    plot(F[0], F[1], 'ro')
                else:
                    plot(F[0], F[1], 'go')
            print(pi/4)
        case 2:
            for _ in range(nr_pcte):
                F = [random(), random()]
                if dist(F, E) < min([dist(F, A), dist(F, B), dist(F, C), dist(F, D)]):
                    count = count + 1
                    plot(F[0], F[1], 'yo')
                else:
                    plot(F[0], F[1], 'bo')
            print(0.5)
        case 3:
            for _ in range(nr_pcte):
                F = [random(), random()]
                if dist(F, E) < F[1]:
                    count = count + 1
                    plot(F[0], F[1], 'yo')
                else:
                    plot(F[0], F[1], 'bo')
            print(2/3)
        case 4:
            for _ in range(nr_pcte):
                F = [random(), random()]
                FA, FB, FC, FD = dist(F, A), dist(F, B), dist(F, C), dist(F, D)
                tri_obtuze = (FA ** 2 + FB ** 2 < 1) + (FB ** 2 + FC ** 2 < 1) + (FC ** 2 + FD ** 2 < 1) + (
                            FD ** 2 + FA ** 2 < 1)
                if tri_obtuze == 2:
                    count = count + 1
                    plot(F[0], F[1], 'go')
                else:
                    plot(F[0], F[1], 'co')
            print(pi/2 - 1)
    show()
    return count/nr_pcte

frecv = patrat(nr_pcte=2000, cerinta=int(input("Introduceti cerinta: ")))
print("Frecventa relativa: ")
print(frecv)