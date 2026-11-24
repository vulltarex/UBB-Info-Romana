from scipy.stats import binom
from matplotlib.pyplot import bar, hist, grid, show, legend
# help('scipy.stats.binom')

data = binom.rvs(5, 0.6, size=1000)

bin_edges = [k-0.5 for k in range(7)]
hist(data, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black',
    alpha = 0.5, label = 'frecvente relative')

distribution = dict([(i,binom.pmf(i,5, 0.6)) for i in range(6)])
bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black',
    alpha = 0.6, label = 'probabilitati')

legend(loc = 'lower left')
grid()
show()
P = binom.cdf(4, 5, 0.6) - binom.cdf(1, 5, 0.6)
print("Probabilitate teoretica 1 < X <= 4: " + str(P))
