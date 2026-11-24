n = int(input("n = "))
if n == 1:
    print("Primul element al sirului este 1")
else:
    cnt = 1
    nr = 2
    while cnt < n:
        divi = 2
        aux = nr
        while aux != 1 and cnt != n:
            ok = 0
            while aux % divi == 0:
                ok = 1
                aux /= divi
            if ok == 1:
                cnt += 1
            if cnt != n:
                divi += 1
        nr += 1
    print(f"Al {n}-lea element al sirului este {divi}")

"""
14 si 2 lab3
"""
