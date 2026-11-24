# Complexitate timp
import time


# T(n) = 10*n -> Theta(n)

def f_1(n: int):
    count = 0
    for i in range(10): 
        for j in range(n):
            count = count + 1
    print(f"f1 n={n}, count={count}")


def f_1_1(lst: list):
    poz = 0
    n = len(lst)
    while poz < n and lst[poz] % 5 != 0:
        poz += 1
    return poz < n


def f_2(n: int):
    count = 0

    for i in range(n, n + 10):  
        for j in range(n):
            count += 1



def f_3(n: int):
    count = 0
    for i in range(1, n):
        for j in range(i, n):
            count += 1
    print(f"f3 n={n}, count={count}")


f_1(5)
f_3(5)
f_3(10)
f_3(15)


def f_10(n: int):
    for i in range(n):
        for j in range(n, i, -1):
            print("Hello World")


def f_4(n: int):
    count = 0

    for i in range(n):
        for j in range(2 * i + 1):
            count += 1
    print(f"f_4 n={n}, count={count}")

f_4(5)
f_4(10)
f_4(15)

def f_5(n: int):
    count = 0

    for i in range(n ** 2):
        for j in range(i):
            count += 1
    print(f"f_5 n={n}, count={count}")

f_5(5)
f_5(10)
f_5(15)

# Theta(nlogn)
def f_6(n: int):
    for i in range(n):  
        t = 1
        while t < n:
            print("Hello World")
            t *= 2


def f_7(n, m: int):
    for i in range(0, n):
        print("Hello World")
    for j in range(0, m):
        print("Hello World")


def f_8(n, m: int):
    for i in range(0, n):
        print("Hello World")
    for j in range(0, n):
        print("Hello World")


def f_9(n: int):
    for i in range(n):
        for j in range(n):
            print("Hello World")
        for k in range(n):
            print("Hello World")


def f_11(n: int):
    s = 0
    for i in range(1, n ** 2+1):
        j = i
        while j != 0:
            s = s + j - 10 * j // 10
            j //= 10
    return s


"""
Recursive functions
"""


def recursive_f_1(n: int):
    if n <= 0:
        return 1
    else:
        return 1 + recursive_f_1(n - 1)


def recursive_f_2(n: int):
    if n <= 1:
        return 1
    else:
        return 1 + recursive_f_2(n - 5)


def recursive_f_3(n: int):
    if n <= 0:
        return 1
    else:
        return 1 + recursive_f_3(n // 2)


def recursive_f_4(n, m, o):
    if n <= 0:
        print('m =', m, "n =", n, "o =", o)
    else:
        recursive_f_4(n - 1, m + 1, o)
        recursive_f_4(n - 1, m, o + 1)


def recursive_f_5(n: int):
    print(n)
    for i in range(n):
        print("Hello world!")
    if n < 1:
        return 1
    else:
        return 1 + recursive_f_5(n - 1)


def recursive_f_6(n, i: int):
    if n > 1:
        i *= 2
        m = n // 2
        recursive_f_6(m, i - 2)
        recursive_f_6(m, i - 1)
        recursive_f_6(m, i + 2)
        recursive_f_6(m, i + 1)
    else:
        print(i)


"""
Analyze the time and space complexity 
"""


def f_12(data: list):
    data_sum = 0
    for el in data:
        j = len(data)
        while j > 1:
            data_sum += el * j
            j = j // 3
    return data_sum


def f_13(data: list):
    if len(data) == 0:
        return 0
    if len(data) == 1:
        return data[0]
    m = len(data) // 2
    return f_13(data[:m]) + f_13(data[m:])


data = list(range(10))
print(data)
print('Original list id:', id(data))
slice = data[:5]
print('Slice up to 5:', slice)
print('Slice id:', id(slice))
slice.append(99)
print('Slice after adding 99:', slice)
print('Data after adding 99 to slice:', data)

data = list(range(1000))
print('Original list id:', id(data))
slice_left = data[:500]
print('Slice data[:5] id:', id(slice_left))
slice_right = data[500:]
print('Slice data[5:] id:', id(slice_right))
print('Original list id after slicing:', id(data))

# def check_execution_time(n: int):
#     print("n=" + str(n))
#     print('O(n):')
#     start_time = time.time()
#     f_1(n)
#     end_time = time.time()
#     print("--- %s seconds ---" % (round(end_time - start_time, 3)))
#
#     print('O(n^2)')
#     start_time = time.time()
#     f_3(n)
#     end_time = time.time()
#     print("--- %s seconds ---" % (round(end_time - start_time, 3)))
#
#     print('O(n^4)')
#     if n>500:
#         print("n^4 means", n**4,'elements')
#         print("Won't compute time. Because it will take a lot. ")
#     else:
#         start_time = time.time()
#         f_5(n)
#         end_time = time.time()
#         print("--- %s seconds ---" % (round(end_time - start_time, 3)))
#     print("========" * 10)
#
#
#
# check_execution_time(10)
# check_execution_time(100)
# check_execution_time(300)
# check_execution_time(500)
# check_execution_time(1000)
# check_execution_time(10000)
# check_execution_time(100000)
