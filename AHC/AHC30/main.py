import sys
import random

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


def solve_Bayes(N, M, eps, fields):
    X = get_X(N, M, fields)
    sum_lll = [0] * len(X)
    while True:

        s = get_s(N)
        r = get_r(s)

        exit(1)

        lll, pl = get_lll(X, s, r)
        sum_lll = [x + y for x, y in zip(sum_lll, lll)]
        max_p = calc_max_normalized_p_from_lll()
        #それぞれの油田の位置の最大確信度の積が90%以上なら答えを出力し，返答が1ならbreakする
        if max_p >= 0.9:
            has_oil = get_has_oil()
            print("a {} {}".format(len(has_oil), ' '.join(map(lambda x: "{} {}".format(x[0], x[1]), has_oil))))
            resp = input()
            if resp == 1:
                break

def main():
    N, M, eps, fields = receive_input()
    
    if M > 2:
        has_oil = solve_DES(N)
        output(has_oil)
    else :
        has_oil = solve_Bayes(N, M, eps, fields)
    

if __name__ == "__main__":
    main()
