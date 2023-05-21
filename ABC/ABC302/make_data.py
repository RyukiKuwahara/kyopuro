import random

with open("input.txt", "w") as f:
    f.write("100000 100000 10000\n")
    for _ in range(100000):
        f.write(str(random.randint(1, 1001001001001001)) + " ")
    f.write("\n")
    for _ in range(100000):
        f.write(str(random.randint(1, 1001001001001001)) + " ")
    f.write("\n")