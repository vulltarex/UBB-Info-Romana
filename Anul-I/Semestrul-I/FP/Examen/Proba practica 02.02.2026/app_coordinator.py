from controller.service import Service
from repository.repo import RepoAutomobile
from ui.console import Console

repo = RepoAutomobile()
srv = Service(repo)
console = Console(srv)

console.meniu()