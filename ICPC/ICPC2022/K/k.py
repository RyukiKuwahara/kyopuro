with open("./in/K/K", "r") as f:
    f = list(f)
    for i in range(len(f)):
        f[i] = f[i].rstrip()
    n = int(f[0])
    f = f[1:]
    for i in range(n):
        f[i] = f[i].replace(" ", "")
        print(len(f[i]))