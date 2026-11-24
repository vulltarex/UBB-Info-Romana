from service.service_antrenamente import *
from ui.console import *

val_antrenament = ValidatorAntrenament()
repo_antrenamente = RepoFileAntrenamente("antrenamente.txt")
srv_antrenamente = ServiceAntrenamente(repo_antrenamente, val_antrenament)
console = Console(srv_antrenamente)

console.run()