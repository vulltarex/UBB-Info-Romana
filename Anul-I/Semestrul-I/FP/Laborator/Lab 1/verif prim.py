def verif_prim(nr):
    if nr <= 1:
        return 0
    div = 2
    while div <= nr // 2:
        if nr % div == 0:
            return 0
        div += 1
    return 1

nr = int(input("Da-mi numarul: "))

if verif_prim(nr) == 1:
    print(f"{nr} este prim")
else:
    print(f"{nr} NU este prim")
