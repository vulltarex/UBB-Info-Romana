from random import sample
from math import comb

def prob_cond(nr_sim):
    countA, countB = 0, 0
    for _ in range(nr_sim):
        bile_extrase = sample(['red','blue','green'],counts=[5,3,2],k=3)
        if 'red' in bile_extrase:
            countA+=1
            if len(set(bile_extrase))==1:
                countB+=1
    return countB/countA

print("Probabilitatea extragerii doar de bile rosii dupa simulari : " + str(prob_cond(10000)))

P = (comb(5, 3) / comb(10, 3)) / (1 - comb(5, 3) / comb(10, 3))
print("Probabilitatea teoretica: " + str(P))

