from scipy.stats import hypergeom, geom

def simuleaza_bilete_necastigatoare(nr_simulari):
    p_castig = sum(hypergeom.pmf(k, 49, 6, 6) for k in range(3, 7))
    return [geom.rvs(p_castig) - 1 for _ in range(nr_simulari)]

def estimare_si_teoretic(necastigatoare, k=10):
    p_castig = sum(hypergeom.pmf(k_succes, 49, 6, 6) for k_succes in range(3, 7))
    p_estimat = sum(1 for x in necastigatoare if x >= k) / len(necastigatoare)
    p_teoretic = geom.sf(k, p_castig)
    return p_estimat, p_teoretic

nr_simulari = 1000
necastigatoare = simuleaza_bilete_necastigatoare(nr_simulari)
p_estimat, p_teoretic = estimare_si_teoretic(necastigatoare)

print(necastigatoare[:20])
print(p_estimat)
print(p_teoretic)
