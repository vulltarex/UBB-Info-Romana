class Sortari:
    @staticmethod
    def sort_bubble(lista: list, key, reverse=False):
        """
        Complexitatea nu este constanta
        Cazul favorabil: Θ(n) - cand lista este deja sortata
        Cazul mediu: 0(n^2)
        Cazul nefavorabil: 0(n^2)
        """
        sortat = True
        for index1 in range(len(lista)):
            for index2 in range(len(lista) - 1):
                if key(lista[index2]) > key(lista[index2 + 1]) and not reverse or key(lista[index2]) < key(lista[index2 + 1]) and reverse:
                    lista[index2], lista[index2 + 1] = lista[index2 + 1], lista[index2]
                    sortat = False
            if sortat:
                break
        return lista

    @staticmethod
    def sort_shell(lista: list, key, reverse=False):
        interval = len(lista) // 2
        while interval > 0:
            for i in range(interval, len(lista)):
                temp = lista[i]
                j = i
                while j >= interval and key(lista[j - interval]) > key(temp) and not reverse or key(lista[j - interval]) < key(temp) and reverse:
                    lista[j] = lista[j - interval]
                    j -= interval

                lista[j] = temp
            interval //= 2

        return lista