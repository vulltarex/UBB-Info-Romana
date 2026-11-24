"""
Generati toate permutarile unei liste care au aspectul de vale (nr descresc pana intr un punct si dupa cresc)
"""

def is_consistent(lst: list) -> bool:
    if len(lst) == len(set(lst)):
        return True
    else:
        return False

def is_solution(lst: list, n: int) -> bool:
    if len(lst) == n:
        cond = 0
        for index in range(1, len(lst)):
            if lst[index] > lst[index - 1]:
                if cond == 0:
                    return False
                elif cond == -1:
                    cond = 1
            if lst[index] < lst[index - 1]:
                if cond == 0:
                    cond = -1
                if cond == 1:
                    return False
                if index == len(lst) - 1:
                    return False
        return True

def back_rec(lst: list, lst_rez: list) -> None:
    lst_rez.append(0)
    for i in range(0, len(lst)):
        lst_rez[-1] = lst[i]
        if is_consistent(lst_rez):
            if is_solution(lst_rez, len(lst)):
                print(lst_rez)
            else:
                back_rec(lst, lst_rez)
    lst_rez.pop()

def back_iterativ(lst):
    stack = [-1]
    while len(stack) > 0:
        chosen = False
        while not chosen and stack[-1] < len(lst) - 1:
            stack[-1] += 1

            if stack[-1] not in stack[:-1]:
                chosen = True

        if chosen:
            if len(stack) == len(lst):
                perm = [lst[i] for i in stack]
                if is_solution(perm, len(lst)):
                    print(perm)
            else:
                stack.append(-1)
        else:
            stack.pop()

def main():
    lst = [int(element) for element in input("Introduceti elementele:").split()]
    print("Recursiv:")
    back_rec(lst, [])
    print("Iterativ:")
    back_iterativ(lst)

main()