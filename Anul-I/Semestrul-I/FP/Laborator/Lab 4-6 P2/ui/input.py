def get_input_id_concurent(nr_concurenti: int) -> int:
    """
    Se citeste si se valideaza ID-ul unui concurent
    :param nr_concurenti: numarul de concurenti inscrisi
    :return: concurent - ID-ul concurentului
    """
    while True:
        try:
            concurent = int(input("Introduceti ID-ul concurentului: "))
            if 1 <= concurent <= nr_concurenti:
                break
            else:
                print("Introduceti un ID valid!")
        except ValueError:
            print("Introduceti un numar intreg!")

    return concurent

def get_input_nr_proba() -> int:
    """
    Se citeste si se valideaza numarul unei probe
    :return: nr_proba - numarul probei
    """
    while True:
        try:
            nr_proba = int(input("Introduceti proba: "))
            if 1 <= nr_proba <= 10:
                break
            else:
                print("Introduceti un numar intre 1 si 10!")
        except ValueError:
            print("Introduceti un numar intreg!")

    return nr_proba

def get_input_scor() -> int:
    """
    Se citeste si se valideaza un scor
    :return: scor - scorul
    """
    while True:
        try:
            scor = int(input("Introduceti scorul: "))
            if 1 <= scor <= 10:
                break
            else:
                print("Introduceti un numar intre 1 si 10!")
        except ValueError:
            print("Introduceti un numar intreg!")

    return scor

def get_input_scor_total() -> int:
    """
    Se citeste o valoare corespunzatoare unei sume de scoruri
    :return: scor_total - scorul total
    """
    while True:
        try:
            scor_total = int(input("Introduceti scorul: "))
            break
        except ValueError:
            print("Introduceti un numar intreg!")

    return scor_total

def get_input_interval(nr_concurenti: int) -> tuple:
    """
    Se citeste si se valideaza un interval de participanti
    :param nr_concurenti: numarul de concurenti inscrisi
    :return: interval_start, interval_end - capetele intervalului de participanti
    """
    while True:
        try:
            interval_start = int(input("Introduceti ID-ul primului concurent: "))
            if 1 <= interval_start <= nr_concurenti:
                break
            else:
                print("Introduceti un ID valid!")
        except ValueError:
            print("Introduceti un numar intreg!")

    while True:
        try:
            interval_end = int(input("Introduceti ID-ul ultimului concurent: "))
            if interval_start <= interval_end <= nr_concurenti:
                break
            else:
                print("Introduceti un ID valid!")
        except ValueError:
            print("Introduceti un numar intreg!")

    return interval_start, interval_end

def get_input_divizor() -> int:
    """
    Se citeste si se valideaza un divizor pentru F5.2
    :return: divizor - numarul cerut
    """
    while True:
        try:
            divizor = int(input("Introduceti un numar natural nenul: "))
            if divizor > 0:
                break
            else:
                print("Introduceti un numar natural nenul!")
        except ValueError:
            print("Introduceti un numar natural nenul!")

    return divizor

def get_command() -> int:
    """
    Se citeste si se valideaza o comanda (numar natural)
    :return: command - comanda citita
    """
    while True:
        try:
            command = int(input("Introduceti o comanda: "))
            break
        except ValueError:
            print("Introduceti un numar natural!")

    return command

def get_command_func() -> str:
    command = input("Introduceti o comanda:")
    return command