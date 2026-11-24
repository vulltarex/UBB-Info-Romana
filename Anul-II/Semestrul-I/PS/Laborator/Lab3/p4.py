from random import randint, sample

def monte_carlo(v):
    k = randint(1,100)
    w = sample(v, k=k)
    return max(w)

v = [i for i in range(1,101)]
rezultate = [monte_carlo(v) for _ in range(1000)]

prob = rezultate.count(100) / 1000
print("Probabilitate estimata: " + str(prob))
prob_teoretica = 1/100 * sum(k/100 for k in range(1,101))
print("Probabilitate teoretica: " + str(prob_teoretica))

