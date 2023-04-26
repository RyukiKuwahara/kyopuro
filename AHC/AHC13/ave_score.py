file = input()
with open("./scores/"+file, "r", encoding="utf-8") as f:
    sum = 0
    f = list(f)
    for line in f:
        line = line.rstrip()
        line = int(line)
        sum += line
    print(sum / len(f))