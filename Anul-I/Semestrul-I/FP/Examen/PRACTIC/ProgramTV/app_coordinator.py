from ui.console import *
from controller.service import *

repo = RepoEmisiune("emisiuni.txt")
srv = Service(repo)
console = Console(srv)

console.meniu()