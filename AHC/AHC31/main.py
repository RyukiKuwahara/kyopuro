import sys

def switch_rect():
    needed_pile_num = dct["pile_cnt"] + pile_num - W
    # print("dct[pile_nums]: ", dct["pile_nums"])
    for pnf in dct["pile_nums"]:
        for rr in r:
            limit_pile_num = W - rr["pile_cnt"]
            for ind, pnt in enumerate(rr["pile_nums"]):
                if ind == min_ind:
                    continue
                diff = pnf - pnt
                if diff >= needed_pile_num and diff <= limit_pile_num:
                    # print(dct["pile_nums"])
                    ind1 = dct["pile_nums"].index(pnf)
                    ind2 = rr["pile_nums"].index(pnt)
                    # print(dct["pile_nums"], rr["pile_nums"])
                    dct["pile_nums"][ind1], rr["pile_nums"][ind2] = rr["pile_nums"][ind2], dct["pile_nums"][ind1]
                    dct["ind"][ind1], rr["ind"][ind2] = rr["ind"][ind2], dct["ind"][ind1]
                    dct["pile_cnt"] -= diff
                    rr["pile_cnt"] += diff
                    # print("swap", ind1, ind2)
                    # print(dct["pile_nums"], rr["pile_nums"])
                    dct["pile_nums"].append(pile_num)
                    dct["pile_cnt"] += pile_num
                    dct["ind"].append(i)
                    return
    print("over", file=sys.stderr)
    exit(1)


# read input
W, D, N = map(int, input().split())
a = []
for d in range(D):
    a.append(list(map(int, input().split())))

# determine rectangles
rect = [[] for _ in range(D)]
for d in range(D):
    # determine split number
    split_nums = [1, 2, 4, 5, 8, 10, 12, 15, 20, 30, 60]
    max_a = 0
    for dd in range(D):
        max_a = max(max_a, a[dd][-1])
    split_ind = 0
    for i, split_num in enumerate(split_nums):
        pile_num = (max_a + W // split_num - 1) // (W // split_num)
        if pile_num > 1000:
            break
        split_ind = i

    split_num = split_nums[split_ind]
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
            switch_rect()
            
    
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
