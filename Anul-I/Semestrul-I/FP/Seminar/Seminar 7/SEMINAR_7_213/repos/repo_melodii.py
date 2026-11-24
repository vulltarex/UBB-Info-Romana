from domain.entities import Melodie


class RepoMelodieMemory:
    """
    Pure fabrication - Repository Pattern
    """

    def __init__(self):
        # cheie=id: valoare=melodie
        self.__melodii = {}
        # self.__melodii = []

    def add(self, melodie: Melodie):
        """
        Adauga o melodie la colectia de melodii
        :param melodie: melodie de adaugat
        :return: -; melodia data a fost adaugata la colectia de melodii
        :raises: ValueError daca exista deja melodie cu id dat
        """
        if melodie.get_id() in self.__melodii:
            raise ValueError("Exista deja melodie cu id dat")
        self.__melodii[melodie.get_id()] = melodie

    def remove(self, m_id: int) -> Melodie:
        """
        Sterge melodie cu id dat
        :param m_id: id-ul melodiei de sters
        :return: melodia stearsa
        :raises: ValueError daca nu exista melodie cu id-ul dat
        """
        if not m_id in self.__melodii:
            raise ValueError(f"Nu exista melodie cu id-ul {m_id}")
        melodie_stearsa = self.__melodii[m_id]
        del self.__melodii[m_id]
        return melodie_stearsa

    def update(self, m_id: int, melodie_noua: Melodie) -> Melodie:
        """
        Actualizeaza o melodie
        :param m_id: id-ul melodiei de actualizat
        :param melodie_noua: melodia cu informatia actualizata
        :return: melodia veche
        :raises: ValueError daca nu exista melodie cu id = m_id
        """
        melodie_veche = self.remove(m_id)
        self.add(melodie_noua)
        return melodie_veche

    def find(self, m_id: int):
        """
        Cauta melodia cu id-ul m_id
        :param m_id: id-ul cautat
        :return: melodia cu id m_id, daca aceasta exista, None altfel
        """
        if not m_id in self.__melodii:
            return None
        return self.__melodii[m_id]

    def size(self):
        """
        Returneaza numarul de melodii
        """
        return len(self.__melodii)

    def get_all(self):
        """
        Returneaza lista de melodii
        :return:
        """
        return self.__melodii.values()
