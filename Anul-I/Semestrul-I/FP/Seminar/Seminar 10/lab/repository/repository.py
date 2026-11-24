from domain.player import Player


class RepositoryException(Exception):
    def __init__(self, message):
        super().__init__("[Repository exception]" + message)


class PlayerAlreadyExistsException(RepositoryException):
    def __init__(self):
        super().__init__("Player already exists.")


class PlayerDoesNotExistException(RepositoryException):
    def __init__(self):
        super().__init__("Player does not exist.")


class PlayersRepositoryMemory:
    def __init__(self):
        # name+country: Player
        self.__players = {}

    def find(self, player_name, player_country) -> Player:
        """
        Cauta un jucator dupa nume si tara de origine
        :param player_name: numele jucatorului
        :param player_country: tara de origine a jucatorului
        :return: jucatorul cu nume player_name si tara de origine player_country daca acesta exista
        :raises: PlayerDoesNotExistException daca jucatorul cu numele si tara date nu exista
        """
        player_key = player_name + '_' + player_country
        if player_key in self.__players:
            return self.__players[player_key]
        else:
            raise PlayerDoesNotExistException()

    def store(self, player: Player):
        """
        Adauga un jucator la colectia de jucatori
        :param player: jucatorul de adaugat (Player)
        :return: -; jucatorul este adaugat la colectie
        :raises: PlayerAlreadyExistsException daca un jucator
                cu acelasi nume si aceeasi tara exista deja
        """
        player_key = player.name + "_" + player.country
        if player_key in self.__players:
            raise PlayerAlreadyExistsException()
        else:
            self.__players[player_key] = player

    @property
    def all(self):
        """
        Returneaza intreaga colectie de jucatori
        """
        return self.__players.values()


class PlayersRepositoryFile(PlayersRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__read_from_file()

    def __read_from_file(self):
        """
        Citeste datele din fisier
        :return:
        """
        with open(self.__filename, mode="r", encoding="utf-8") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    name, country, matches_played, matches_won, points = line.split(",")
                    matches_played = int(matches_played)
                    matches_won = int(matches_won)
                    points = int(points)
                    p = Player(name.strip(), country.strip(), matches_played, matches_won, points)
                    super().store(p)

    def store(self, player: Player):
        super().store(player)
        self.__save_to_file()

    def __save_to_file(self):
        """
        Salveaza datele in fisier
        :return:
        """
        with open(self.__filename, mode="w", encoding="utf-8") as f:
            for player in self.all:
                player_str = player.name + "," + player.country + "," + str(player.matches_played) + "," + str(
                    player.matches_won) + "," + str(player.points) + "\n"
                f.write(player_str)
