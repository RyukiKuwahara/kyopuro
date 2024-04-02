import sys
import copy
import bisect

def calculate_rectangle_area(i0, j0, i1, j1):
    width = abs(j1 - j0)
    height = abs(i1 - i0)
    return width * height

def swap_rect():
    # print("call swap_rect")
    # print("\t", r)
    needed_pile_num = dct["pile_cnt"] + pile_num - W
    # print(r, needed_pile_num)
    # print("dct[pile_nums]: ", dct["pile_nums"])
    for pnf in dct["pile_nums"]:
        for ind, rr in enumerate(r):
            if ind == min_ind:
                continue
            # print("limit", limit_pile_num)
            for pnt in rr["pile_nums"]:
                limit_pile_num = W - rr["pile_cnt"]
                diff = pnf - pnt
                # print("\t", "pnf: ", pnf, "pnt: ", pnt)
                if diff > 0 and diff <= limit_pile_num:
                    # print("swap")
                    # print(dct["pile_nums"])
                    ind1 = dct["pile_nums"].index(pnf)
                    ind2 = rr["pile_nums"].index(pnt)
                    # print("\t", dct["pile_nums"], rr["pile_nums"])
                    dct["pile_nums"][ind1], rr["pile_nums"][ind2] = rr["pile_nums"][ind2], dct["pile_nums"][ind1]
                    dct["ind"][ind1], rr["ind"][ind2] = rr["ind"][ind2], dct["ind"][ind1]
                    dct["pile_cnt"] -= diff
                    rr["pile_cnt"] += diff
                    pnf = pnt
                    # print("\t", "swap", ind1, ind2)
                    # print("\t", dct["pile_nums"], rr["pile_nums"], "\n")
                    # print("\t", "pile_cnt", dct["pile_cnt"])
                    if dct["pile_cnt"] + pile_num <= W:
                        dct["pile_nums"].append(pile_num)
                        dct["pile_cnt"] += pile_num
                        dct["ind"].append(i)
                        # if dct["pile_cnt"] > W:
                        #     print("\t", r)
                        return True
                
    # print("over", file=sys.stderr)
    return False

def eval_area_cost(a, rects):
    cost = 0
    for i in range(len(a)):
        # print(rects[i][3] - rects[i][1], rects[i][4] - rects[i][2])
        diff = a[i] - (rects[i][3] - rects[i][1]) * (rects[i][4] - rects[i][2])
        # print(diff, a[i], (rects[i][3] - rects[i][1]) * (rects[i][4] - rects[i][2]))
        if diff > 0:
            cost += 100 * diff
    return cost

def eval_move_cost(N, f, t):
    if f == -1 and t == -1:
        return N * 500 * 2
    elif f == -1:
        return N * 500 + t * W + W // t * N * 2
    elif t == -1:
        return N * 500 + f * W + W // f * N * 2
    else:
        cost = 0
        if f != t:
            cost += (f + t) * W
        cost += W // f * N * 2 + W // t * N * 2
        return cost


# read input
W, D, N = map(int, input().split())
a = []
for d in range(D):
    a.append(list(map(int, input().split())))

# determine rectangles
rect = [[] for _ in range(D)]
cost = 0
for d in range(D):
    # determine max split number
    split_nums = [1, 2, 4, 5, 8, 10, 12, 15, 20, 30, 60]
    max_a = a[d][-1]
    max_split_ind = 0
    for i, split_num in enumerate(split_nums):
        pile_num = (max_a + W // split_num - 1) // (W // split_num)
        if pile_num > 1000:
            break
        max_split_ind = i

    
    # determine position
    for split_ind in range(max_split_ind + 1):
        split_num = split_nums[split_ind]
        r = [{"pile_cnt" : 0, "pile_nums" : [], "ind" : []} for _ in range(split_num)]
        for i, a_dk in enumerate(a[d][::-1]):
            # search min pile_cnt index
            min_ind = 0
            for j, _ in enumerate(r):
                if r[j]["pile_cnt"] < r[min_ind]["pile_cnt"]:
                    min_ind = j

            dct = r[min_ind]
            if dct["pile_cnt"] == W:
                # print(dct["pile_nums"])
                max_ind = dct["pile_nums"].index(max(dct["pile_nums"]))
                dct["pile_nums"][max_ind] -= 1
                dct["pile_cnt"] -= 1
                # print(dct["pile_nums"])

            pile_num = (a_dk + W // split_num - 1) // (W // split_num)
            if dct["pile_cnt"] + pile_num <= W:
                dct["pile_nums"].append(pile_num)
                dct["pile_cnt"] += pile_num
                dct["ind"].append(i) 
            else:
                if not swap_rect():
                    # print(dct, pile_num)
                    pile_num -= dct["pile_cnt"] + pile_num - W
                    dct["pile_nums"].append(pile_num)
                    dct["pile_cnt"] += pile_num
                    dct["ind"].append(i)
                    # print(dct)

            # if dct["pile_cnt"] > W:
            #     print(r)
                    
        
        rect_d = []
        for i, dct in enumerate(r):
            s_i = 0
            for pile_num, ind in zip(dct["pile_nums"], dct["ind"]):
                rect_d.append((ind, s_i, W // split_num * i, s_i + pile_num, W // split_num * (i + 1)))
                s_i += pile_num

        rect_d = sorted(rect_d, key=lambda x: x[0], reverse=True)
        rect[d].append(rect_d)

    rect_special = []
    tate, yoko = W, W
    used = [False for _ in range(N)]
    for i, a_dk in enumerate(a[d][::-1]):
        if used[N - i - 1]:
            continue
        if tate >= yoko:
            start_of_pile_num = (a_dk + yoko - 1) // yoko
            if tate - start_of_pile_num <= 0:
                rect_special.append((N - i - 1, W - tate, W - yoko, W - tate + 1, W))
                tate -= 1
                continue
            useless_area = abs(a_dk - yoko * start_of_pile_num)
            candidates = [(N - i - 1, W - tate, W - yoko, W - tate + start_of_pile_num, W)]
            for pile_num in range(start_of_pile_num, min(W, start_of_pile_num * 2)):
                diff = yoko * pile_num - a_dk
                upper = diff // pile_num * pile_num
                ind = bisect.bisect_right(a[d], upper) - 1
                if ind < 0 or ind == N - i - 1:
                    continue

                area1 = calculate_rectangle_area(W - tate, W - yoko, W - tate + pile_num, W - diff // pile_num)
                area2 = calculate_rectangle_area(W - tate, W - diff // pile_num, W - tate + pile_num, W)

                if not used[ind] and abs(abs(a_dk - area1) + abs(a[d][ind] - area2)) < useless_area:
                    useless_area = abs(abs(a_dk - area1) + abs(a[d][ind] - area2))
                    candidates = []
                    candidates.append((N - i - 1,  W - tate, W - yoko, W - tate + pile_num, W - diff // pile_num))
                    candidates.append((ind, W - tate, W - diff // pile_num, W - tate + pile_num, W))
            
            for candidate in candidates:
                rect_special.append(candidate)
                used[candidate[0]] = True
                pile_num = candidate[3] - candidate[1]
            tate -= pile_num
        else :
            start_of_pile_num = (a_dk + tate - 1) // tate
            if yoko - start_of_pile_num <= 0:
                rect_special.append((N - i - 1, W - tate, W - yoko, W, W - yoko + 1))
                yoko -= 1
                continue
            useless_area = abs(a_dk - tate * start_of_pile_num)
            candidates = [(N - i - 1, W - tate, W - yoko, W, W - yoko + start_of_pile_num)]
            for pile_num in range(start_of_pile_num, min(W, start_of_pile_num * 2)):
                diff = tate * pile_num - a_dk
                upper = diff // pile_num * pile_num
                ind = bisect.bisect_right(a[d], upper) - 1
                if ind < 0 or ind == N - i - 1:
                    continue

                area1 = calculate_rectangle_area(W - tate, W - yoko, W - diff // pile_num, W - yoko + pile_num)
                area2 = calculate_rectangle_area(W - diff // pile_num, W - yoko, W, W - yoko + pile_num)

                if not used[ind] and abs(abs(a_dk - area1) + abs(a[d][ind] - area2)) < useless_area:
                    useless_area = abs(abs(a_dk - area1) + abs(a[d][ind] - area2))
                    candidates = []
                    candidates.append((N - i - 1,  W - tate, W - yoko, W - diff // pile_num, W - yoko + pile_num))
                    candidates.append((ind, W - diff // pile_num, W - yoko, W, W - yoko + pile_num))
            
            for candidate in candidates:
                rect_special.append(candidate)
                used[candidate[0]] = True
                pile_num = candidate[4] - candidate[2]
            yoko -= pile_num

    rect[d].append(sorted(rect_special, key=lambda x: x[0]))

candinates = []
for i in range(len(rect[0])):
    cost = eval_area_cost(a[0], rect[0][i])
    if i == len(rect[0]) - 1:
        candinates.append({"cost":cost, "path":[-1]})
    else:
        candinates.append({"cost":cost, "path":[i]})

for d in range(D-1):
    new_candinates = []
    for candinate in candinates:
        for j in range(len(rect[d+1])):
            # print(candinate, candinate["path"][-1])
            if candinate["path"][-1] == -1:
                f = -1
            else:
                f = split_nums[candinate["path"][-1]]

            if j == len(rect[d+1]) - 1:
                t = -1
            else:
                t = split_nums[j]
            cost = candinate["cost"] + eval_move_cost(N, f, t) + eval_area_cost(a[d+1], rect[d+1][j])
            # if d == 0:
            #     print("f", f, "t", t, "candi[cost]", candinate["cost"], "move cost", eval_move_cost(N, f, t), "area cost", eval_area_cost(a[d+1], rect[d+1][j]))
            path = copy.deepcopy(candinate["path"])
            if j == len(rect[d+1]) - 1:
                path.append(-1)
            else:
                path.append(j)

            new_candinates.append({"cost":cost, "path":path})
    new_candinates = sorted(new_candinates, key=lambda x: x["cost"])[:30]
    candinates = new_candinates
    # print(candinates)

best_path = candinates[0]["path"]
# print(candinates)
# output
for d in range(D):
    ind = best_path[d]
    for ele in rect[d][ind]:
        i0, j0, i1, j1 = ele[1:]
        print(i0, j0, i1, j1)
