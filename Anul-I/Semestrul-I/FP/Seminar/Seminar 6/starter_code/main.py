import sys

"""
Exchange rates:
1 EUR - 1.16 USD
      - 5.09 RON
"""
from currency import Currency

v1 = Currency(15, "EUR")
v2 = Currency(12.725, "RON")

# print(v1)
# print(v2)

v3 = v1 + v2

# ar trebui sa afiseze Money: 17.5 EUR
# adaugarea se face in currency unit al v1
print(v3)

v4 = Currency(20)
v5 = v3 + v4

# ar trebui sa afiseze Money: 37.5 EUR (v3 = 17.5 + v4 = 20 EUR)
print(v5)
v6 = Currency()
v7 = v6 + v5
# ar trebui sa afiseze Money: 37.5 EUR (v5 = 37.5 + v6 = O EUR)
print(v7)

v8 = Currency(20, "RON")
v9 = Currency(5.8, "USD")

# ar trebui sa afiseze Money: 45.45 RON (v8 = 20 RON + v9 = 5.8 USD =
# 5.8 USD = 5.8/1.16 EUR * 5.09 = 25.45 RON
print(v8 + v9)
# ar trebui sa afiseze Money: 18 EUR (int sau float simplu sunt considerate ca
# amount, iar pentru ele currency_unit = EUR)
print(v1 + 3)

try:
    v8 = v1 + "20RON"
except TypeError as e:
    # se afiseaza "Nu se poate efectua adaugarea."
    print(e)

# ar trebui sa afiseze Money: 25 EUR (int sau float simplu sunt considerate ca
# amount, iar pentru ele currency_unit = EUR)
print(10 + v1)
# c1 = Currency(15, "EUR")
# print(id(c1))
# c1 += 3
# print(id(c1))
# print(c1)

v9 = Currency(20.36, "RON")
v10 = Currency(4, "EUR")
# v11 = Currency(4, "EUR")
# ar trebui sa se afiseze True
assert (v9 == v10)

v1 = Currency.from_string("20 USD")
print(v1)
# have to implement __lt__ for this to work
# print(v9<v10)
