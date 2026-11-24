def este_prim(nr):
    if nr <= 1:
        return 0
    else:
        divi = 2
        while divi <= nr // 2:
            if nr % divi == 0:
                return 0
            divi += 1
        return 1

n = int(input("n = "))
if n == 1:
    print(1)
else:
    nr = 2
    cnt = 1
    while cnt < n:        
        if este_prim(nr):
            cnt += 1
            divi = nr
        else:
            aux = nr
            divi = 2
            while aux != 1 and cnt != n:
                if aux % divi == 0:
                    for i in range(divi):
                        cnt += 1
                        if cnt == n:
                            break
                    while aux % divi == 0:
                        aux /= divi
                if cnt != n:
                    divi += 1
        nr += 1
    print(f"Al {n}-lea element al sirului este {divi}")
