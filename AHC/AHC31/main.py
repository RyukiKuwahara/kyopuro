import sys
# read input
W, D, N = map(int, input().split())
a = []
for d in range(D):
    a.append(list(map(int, input().split())))

# determine rectangles
rect = [[] for _ in range(D)]
for d in range(D):
    # determine split number
    flag = True
    split_num = 1
    while flag:
        pile_cnt = 0
        for a_dk in a[d]:
            pile_cnt += (a_dk + W // split_num - 1) // (W // split_num)

        if pile_cnt < W * split_num:
            break
        else:
            split_num *= 2

    # determine position
    r = [{"pile_cnt" : 0, "pile_nums" : [], "ind" : []} for _ in range(split_num)]
    for i, a_dk in enumerate(a[d][::-1]):
        # search min pile_cnt index
        min_ind = 0
        for j, _ in enumerate(r):
            if r[j]["pile_cnt"] < r[min_ind]["pile_cnt"]:
                min_ind = j

        dct = r[min_ind]
        pile_num = (a_dk + W // split_num - 1) // (W // split_num)
        if dct["pile_cnt"] + pile_num <= W:
            dct["pile_nums"].append(pile_num)
            dct["pile_cnt"] += pile_num
            dct["ind"].append(i)
        else:
            print("over", file=sys.stderr)
    
    rect_d = []
    for i, dct in enumerate(r):
        s_i = 0
        for pile_num, ind in zip(dct["pile_nums"], dct["ind"]):
            rect_d.append((ind, s_i, W // split_num * i, s_i + pile_num, W // split_num * (i + 1)))
            s_i += pile_num
    rect_d = sorted(rect_d, key=lambda x: x[0])
    rect[d] = rect_d
    

# output
for d in range(D):
    for ele in rect[d][::-1]:
        i0, j0, i1, j1 = ele[1:]
        print(i0, j0, i1, j1)
