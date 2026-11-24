from domain.validator import ValidatorMelodie
from repos.repo_melodii import RepoMelodieMemory
from services.service_melodii import ServiceMelodii
from ui.console import Console

repo = RepoMelodieMemory()
val = ValidatorMelodie()
srv = ServiceMelodii(repo, val)
console = Console(srv)
console.run()
