from domain.validator import PlayerValidator
from repository.repository import PlayersRepositoryFile
from service.player_service import PlayerService
from ui.console import Console

repo = PlayersRepositoryFile("data/players.txt")

validator = PlayerValidator()
srv = PlayerService(repo, validator)
console = Console(srv)
console.run()