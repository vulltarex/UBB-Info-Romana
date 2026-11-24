def cmmdc(a, b):
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

a = int(input("primul numar: "))
b = int(input("al doilea numar: "))

print(f"Cel mai mare divizor comun este {cmmdc(a, b)}")
            
    
