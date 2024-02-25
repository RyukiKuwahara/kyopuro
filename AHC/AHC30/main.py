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
            if random_number <= 0.1:
                s.append([i, j])
    return s

#Sは占いをするためのマス集合
def get_S(N, t):
    S = []
    for _ in range(t):
        s = get_s(N)
        S.append(s)
    return S

def solve_Bayes(N, M, eps, fields):
    X, p_X = get_X()
    while True:

        s = get_s(N)
        r = get_r(s)

        p_correct, pl = calc_p_correct(X, p_X, s, r)
        #それぞれの油田の位置の最大確信度の積が90%以上なら答えを出力し，返答が1ならbreakする
        if p_correct >= 0.9:
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
        has_oil = solve_Bayes()
    

if __name__ == "__main__":
    main()
