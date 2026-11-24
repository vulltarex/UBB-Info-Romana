import random
import string

# Generates a string of a specific length using printable ASCII characters
garbage_string = ''.join(random.choice(string.printable) for _ in range(65536))

with open("garbage.txt", "w", encoding="utf-8") as f:
    f.write(garbage_string)

