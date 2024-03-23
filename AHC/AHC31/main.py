# read input
W, D, N = map(int, input().split())
a = []
for d in range(D):
    a.append(list(map(int, input().split())))

# determine rectangles
rect = [[] for _ in range(D)]
for d in range(D):
    s_i = 0
    for k in range(N):
        a_dk = a[d][k]
        g_i = min(W, s_i + (a_dk + W - 1) // W)
        rect[d].append((s_i, 0, g_i, W))
        s_i = g_i + 1

# output
for d in range(D):
    for k in range(N):
        i0, j0, i1, j1 = rect[d][k]
        print(i0, j0, i1, j1)
