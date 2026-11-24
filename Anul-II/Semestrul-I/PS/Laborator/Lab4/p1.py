from scipy.stats import bernoulli, binom
from matplotlib.pyplot import bar, show, hist, grid, legend, xticks

def deplasare_axa(N, p):
    pozitie_curenta = 0
    pozitii = [pozitie_curenta]

    pasi = 2 * bernoulli.rvs(p, size=N) - 1

    for pas in pasi:
        pozitie_curenta += int(pas)
        pozitii.append(pozitie_curenta)

    return pozitii

def histograma_simulari(N, p, nr_simulari=1000):
    pozitii_finale = [deplasare_axa(N, p)[-1] for _ in range(nr_simulari)]

    bin_edges = [x - 0.5 for x in range(-N, N + 2)]
    hist(pozitii_finale, bins=bin_edges, density=True, label='simulare')

    k_valori = list(range(N + 1))
    pozitii_teoretice = [2 * k - N for k in k_valori]
    probabilitati = [binom.pmf(k, N, p) for k in k_valori]
    bar(pozitii_teoretice, probabilitati, width=0.5, alpha=0.5, label='teoretic')

    xticks(pozitii_teoretice)
    grid()
    legend()
    show()

def deplasare_cerc(N, p, n):
    pozitie_curenta = 0
    pozitii = [pozitie_curenta]

    pasi = 2 * bernoulli.rvs(p, size=N) - 1

    for pas in pasi:
        pozitie_curenta = (pozitie_curenta + int(pas)) % n
        pozitii.append(pozitie_curenta)

    return pozitii

def histograma_cerc(N, p, n, nr_simulari=1000):
    pozitii_finale = [deplasare_cerc(N, p, n)[-1] for _ in range(nr_simulari)]

    bin_edges = [x - 0.5 for x in range(n + 1)]
    hist(pozitii_finale, bins=bin_edges, density=True, label='simulare')

    probabilitati = [0.0] * n
    for k in range(N + 1):
        nod = (2 * k - N) % n
        probabilitati[nod] += binom.pmf(k, N, p)
    bar(range(n), probabilitati, width=0.5, alpha=0.5, label='teoretic')

    xticks(range(n))
    grid()
    legend()
    show()

print(deplasare_axa(N=10, p=0.5))
histograma_simulari(N=10, p=0.5)

print(deplasare_cerc(N=10, p=0.5, n=5))
histograma_cerc(N=10, p=0.5, n=5)
