def validare_scor(scor: str) -> bool:
    """
    Valideaza scorul introdus de utilizator
    :param scor: scorul introdus de utilizator
    :return: true/false pentru validare
    """
    try:
        scor = int(scor)
    except ValueError:
        return False
    if 1 <= scor <= 10:
        return True
    else:
        return False

def validare_nr_proba(nr_proba: str) -> bool:
    """
    Valideaza numarul unei probe introduse de utilizator
    :param nr_proba: numarul probei
    :return: true/false pentru validare
    """
    try:
        nr_proba = int(nr_proba)
    except ValueError:
        return False
    if 1 <= nr_proba <= 10:
        return True
    else:
        return False

def validare_id_concurent(id_concurent: str, nr_concurenti: int) -> bool:
    """
    Valideaza ID-ul unui concurent introdus de utilizator
    :param id_concurent: ID-ul concurentului
    :param nr_concurenti: numarul de concurenti inscrisi
    :return: true/false pentru validare
    """
    try:
        id_concurent = int(id_concurent)
    except ValueError:
        return False
    if 1 <= id_concurent <= nr_concurenti:
        return True
    else:
        return False