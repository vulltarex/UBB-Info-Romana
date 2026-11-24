class Player:
    def __init__(self, name, country, matches_played, matches_won, points):
        self.__name = name
        self.__country = country
        self.__matches_played = matches_played
        self.__matches_won = matches_won
        self.__points = points

    @property
    def name(self):
        return self.__name

    @property
    def country(self):
        return self.__country

    @property
    def matches_played(self):
        return self.__matches_played

    @property
    def matches_won(self):
        return self.__matches_won

    @property
    def points(self):
        return self.__points

    @name.setter
    def name(self, value):
        self.__name = value

    # player.set_country("new country")
    # def set_country(self, value):
    #     self.__country = value

    # player.country = "new country"
    @country.setter
    def country(self, value):
        self.__country = value

    @matches_played.setter
    def matches_played(self, value):
        self.__matches_played = value

    @matches_won.setter
    def matches_won(self, value):
        self.__matches_won = value

    @points.setter
    def points(self, value):
        self.__points = value

    def __eq__(self, other):
        if type(other) != type(self):
            return False
        return self.__name == other.__name and self.__country == other.__country

    def __str__(self):
        return "[Player] Name=" + self.__name + " | Country=" + self.__country + " | Match stats: " + str(
            self.__matches_won) + "/" + str(self.matches_played) + " | Points=" + str(self.__points)
