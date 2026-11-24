class Melodie:
    def __init__(self, m_id: int, titlu: str, artist: str, gen: str, durata: float):
        self.__id = m_id
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata

    def get_id(self):
        return self.__id

    def get_artist(self):
        return self.__artist

    def get_gen(self):
        return self.__gen

    def get_titlu(self):
        return self.__titlu

    def get_durata(self):
        return self.__durata

    # TO DO: add the other setters
    def set_titlu(self, titlu_nou):
        self.__titlu = titlu_nou

    def __str__(self):
        return f"Melodie #{self.__id} (titlu = {self.__titlu}; artist = {self.__artist}; gen = {self.get_gen()}; durata = {self.get_durata()})"

    # @property
    # def id_melodie(self):
    #     print("ID melodie property")
    #     return self.__id

# m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
# print(m)
# info = "Info"+str(m)
# print(info)

# TO-DO:
# add tests for entities (create, getters, setters)
