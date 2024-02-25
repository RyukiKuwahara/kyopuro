import sys
import random
import math


def receive_input():
    # read prior information
    line = input().split()
    N = int(line[0])
    M = int(line[1])
    eps = float(line[2])
    fields = []
    for _ in range(M):
        line = input().split()
        ps = []
        for i in range(int(line[0])):
            ps.append((int(line[2*i+1]), int(line[2*i+2])))
        fields.append(ps)
    return N, M, eps, fields

def solve_DES(N):
    # drill every square
    has_oil = []
    for i in range(N):
        for j in range(N):
            print("q 1 {} {}".format(i, j))
            resp = input()
            if resp != "0":
                has_oil.append((i, j))
    return has_oil

def output(has_oil):
    print("a {} {}".format(len(has_oil), ' '.join(map(lambda x: "{} {}".format(x[0], x[1]), has_oil))))
    resp = input()
    assert resp == "1"

#sは占いをするためのマス
def get_s(N):
    s = []
    for i in range(N):
        for j in range(N):
            random_number = random.random()
            #0.25以下ならそのマスを占う
            if random_number <= 0.25:
                s.append((i, j))
    return s

#Sは占いをするためのマス集合
def get_S(N, t):
    S = []
    for _ in range(t):
        s = get_s(N)
        S.append(s)
    return S

def calc_max_len_ij(field):
    max_i, max_j = 0, 0
    for i, j in field:
        max_i = max(max_i, i)
        max_j = max(max_j, j)
    return max_i, max_j

#油田の場所を全列挙
def get_X(N, M, fields):
    X = []
    if M == 1:
        max_i, max_j = calc_max_len_ij(fields[0])
        for i in range(N - max_i):
            for j in range(N - max_j):
                X.append([(i, j)])
    elif M == 2:
        max_i, max_j = calc_max_len_ij(fields[0])
        max_k, max_l = calc_max_len_ij(fields[1])
        for i in range(N - max_i):
            for j in range(N - max_j):
                for k in range(N - max_k):
                    for l in range(N - max_l):
                        X.append([(i, j), (k, l)])
    else:
        sys.stderr.write("油田全列挙でMが1, 2以外が呼ばれました.\n")
        exit(1)
    return X

def get_r(s):
    print("q {} {}".format(len(s), ' '.join(map(lambda x: "{} {}".format(x[0], x[1]), s))))
    r = int(input())
    return r

def create_field(N, ele):
    field = [[ele for _ in range(N)] for _ in range(N)]
    return field

def calc_overlap_sum(fields, s, x, N):
    s_field = create_field(N, False)
    x_field = create_field(N, 0)

    for i, j in s:
        s_field[i][j] = True
    for k, (si, sj) in enumerate(x):
        for i, j in fields[k]:
            x_field[si+i][sj+j] += 1
    cnt = 0
    for i in range(N):
        for j in range(N):
            if s_field[i][j] == True:
                cnt += x_field[i][j]
    return cnt

def cnd(x):
    return (1 + math.erf(x / math.sqrt(2))) / 2

def calc_p_in_range(mu, delta, r, eps):
    # 標準正規分布への変換
    z_lower = (r - 0.5 - mu) / delta
    z_upper = (r + 0.5 - mu) / delta
    
    # 累積分布関数の計算
    prob_lower = cnd(z_lower)
    prob_upper = cnd(z_upper)
    # print(z_lower, z_upper, prob_lower, prob_upper, file=sys.stderr)
    
    # 範囲内の確率を求める
    p = max(eps, prob_upper - prob_lower)

    return p

def calc_mu_delta(k, vs, eps):
    mu = (k - vs) * eps + vs * (1 - eps)
    delta = math.sqrt(k * eps * (1 - eps))
    return mu, delta

def get_lll(fields, X, s, r, N, eps):
    lll = []
    for x in X:
        vs = calc_overlap_sum(fields, s, x, N)
        k = len(s)
        mu, delta = calc_mu_delta(k, vs, eps)
        
        p = calc_p_in_range(mu, delta, r, 1/len(X)*1e-2)
        lll.append(math.log(p))
    return lll

def get_has_oil(x, fields):
    has_oil = set()
    for k, (si, sj) in enumerate(x):
        for i, j in fields[k]:
            has_oil.add((si+i, sj+j))
    return has_oil

def solve_Bayes(N, M, eps, fields):
    X = get_X(N, M, fields)
    sum_lll = [0] * len(X)

    pre_ind = -1
    cnt = 0
    while True:
        cnt += 1

        s = get_s(N)
        r = get_r(s)

        lll = get_lll(fields, X, s, r, N, eps)
        sum_lll = [x + y for x, y in zip(sum_lll, lll)]

        max_ll = max(sum_lll)
        max_ind = sum_lll.index(max_ll)
        x = X[max_ind]
        # print("#pre_ind:{}, max_ind:{}".format(pre_ind, max_ind))
        # for i, j in x:
        #     print("#c {} {} red".format(i, j))
        
        #最も尤度が高い油田の位置が前回の結果と同じなら答えを出力し，返答が1ならbreakする
        if cnt > 10 and max_ind == pre_ind:
            has_oil = get_has_oil(x, fields)
            print("a {} {}".format(len(has_oil), ' '.join(map(lambda x: "{} {}".format(x[0], x[1]), has_oil))))
            resp = input()
            if resp == "1":
                break

        pre_ind = max_ind

def main():
    N, M, eps, fields = receive_input()
    
    if M > 2:
        has_oil = solve_DES(N)
        output(has_oil)
    else :
        has_oil = solve_Bayes(N, M, eps, fields)
    

if __name__ == "__main__":
    main()
