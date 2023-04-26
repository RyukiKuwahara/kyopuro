#include <bits/stdc++.h>
#include <sys/time.h>

using namespace std;




struct MoveAction {
    int before_row, before_col, after_row, after_col;
    MoveAction(int before_row, int before_col, int after_row, int after_col) : 
        before_row(before_row), before_col(before_col), after_row(after_row), after_col(after_col) {}
};

struct ConnectAction {
    int c1_row, c1_col, c2_row, c2_col;
    ConnectAction(int c1_row, int c1_col, int c2_row, int c2_col) : 
        c1_row(c1_row), c1_col(c1_col), c2_row(c2_row), c2_col(c2_col) {}
};

struct Result {
    vector<MoveAction> move;
    vector<ConnectAction> connect;
    Result(const vector<MoveAction> &move, const vector<ConnectAction> &con) : move(move), connect(con) {}
};

struct UnionFind {
    map<pair<int,int>, pair<int, int>> parent;
    UnionFind() :parent() {}

    pair<int, int> find(pair<int, int> x)
    {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            return x;
        } else if (parent[x] == x) {
            return x;
        } else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void unite(pair<int, int> x, pair<int, int> y)
    {
        x = find(x);
        y = find(y);
        if (x != y) {
            parent[x] = y;
        }
    }
};

struct Solver {
    char USED = 'x';
    int DR[4] = {0, 1, 0, -1};
    int DC[4] = {1, 0, -1, 0};

    int N, K;
    int action_count_limit;
    mt19937 engine;
    vector<string> field;

    Solver(int N, int K, const vector<string> &field, int seed = 0) : 
        N(N), K(K), action_count_limit(K * 100), field(field)
    {
        engine.seed(seed);
    }

    bool can_move(int row, int col, int dir) const
    {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        if (0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            return field[nrow][ncol] == '0';
        }
        return false;
    }

    vector<MoveAction> move(int move_limit = -1)
    {
        vector<MoveAction> ret;
        if (move_limit == -1) {
            move_limit = K * 5;
        }

        for (int i = 0; i < move_limit; i++) {
            int row = engine() % N;
            int col = engine() % N;
            int dir = engine() % 4;
            if (field[row][col] != '0' && can_move(row, col, dir)) {
                swap(field[row][col], field[row + DR[dir]][col + DC[dir]]);
                ret.emplace_back(row, col, row + DR[dir], col + DC[dir]);
                action_count_limit--;
            }
        }
        return ret;
    }

    bool can_connect(int row, int col, int dir) const
    {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while (0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if (field[nrow][ncol] == field[row][col]) {
                return true;
            } else if (field[nrow][ncol] != '0') {
                return false;
            }
            nrow += DR[dir];
            ncol += DC[dir];
        }
        return false;
    }

    ConnectAction line_fill(int row, int col, int dir)
    {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while (0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if (field[nrow][ncol] == field[row][col]) {
                return ConnectAction(row, col, nrow, ncol);
            }
            assert(field[nrow][ncol] == '0');
            field[nrow][ncol] = USED;
            nrow += DR[dir];
            ncol += DC[dir];
        }
        assert(false);
    }

    vector<ConnectAction> connect()
    {
        vector<ConnectAction> ret;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] != '0' && field[i][j] != 'x') {
                    for (int dir = 0; dir < 2; dir++) {
                        if (can_connect(i, j, dir)) {
                            ret.push_back(line_fill(i, j, dir));
                            action_count_limit--;
                            if (action_count_limit <= 0) {
                                return ret;
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }


    Result solve()
    {
        // create random moves
        auto moves = move();
        // from each computer, connect to right and/or bottom if it will reach the same type
        auto connects = connect();

        return Result(moves, connects);
    }
};


int calc_score(int N, vector<string> field, const Result &res)
{
    for (auto r : res.move) {
        assert(field[r.before_row][r.before_col] != '0');
        assert(field[r.after_row][r.after_col] == '0');
        swap(field[r.before_row][r.before_col], field[r.after_row][r.after_col]);
    }

    UnionFind uf;
    for (auto r : res.connect) {
        pair<int, int> p1(r.c1_row, r.c1_col), p2(r.c2_row, r.c2_col);
        uf.unite(p1, p2);
    }

    vector<pair<int, int>> computers;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (field[i][j] != '0') {
                computers.emplace_back(i, j);
            }
        }
    }

    int score = 0;
    map<pair<int,int>, int> cnt_parent;
    for (auto ele : computers){
        cnt_parent[uf.find(ele)]++;
    }
    for (auto ele : cnt_parent){
        score += ele.second * (ele.second - 1) / 2;
    }


    return max(score, 0);
}

void print_answer(const Result &res)
{
    cout << res.move.size() << endl;
    for (auto m : res.move) {
        cout << m.before_row << " " << m.before_col << " "
            << m.after_row << " " << m.after_col << endl;
    }
    cout << res.connect.size() << endl;
    for (auto m : res.connect) {
        cout << m.c1_row << " " << m.c1_col << " "
            << m.c2_row << " " << m.c2_col << endl;
    }
}

vector<string> extract_used(int N, vector<string> field){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (field[i][j] == 'x') field[i][j] = '0';
        }
    }
    return field;
}

void all_print_answer(vector<Result> rets){
    vector<MoveAction> moves;
    vector<ConnectAction> connects;
    for (int i = 0; i < rets.size(); i++){
        for (auto m : rets[i].move){
            moves.emplace_back(m.before_row, m.before_col, m.after_row, m.after_col);
        }
        if (i == rets.size() - 1){
            connects = rets[i].connect;
        }
    }
    Result ans(moves, connects);
    print_answer(ans);
}


int main()
{
    srand((unsigned int)time(NULL));
    int N, K;
    cin >> N >> K;
    vector<string> field(N);
    for (int i = 0; i < N; i++) {
        cin >> field[i];
    }

    struct timeval start, mid, end;
    gettimeofday(&start, nullptr);
    int move_limit = 100 * K;
    int score = 0;
    vector<Result> rets;
    while(1) {
        gettimeofday(&mid, NULL);
        const int sampling = 75;
        int sampling_best_score = -1;
        Solver best_s(N, K, field);
        auto best_ret = best_s.solve();
        for (int i = 0; i < sampling; i++){
            Solver s(N, K, field, rand());
            auto ret = s.solve();
            int sampling_score = calc_score(N, field, ret);
            // cout << "sampling_score" << sampling_score << endl;
            if (sampling_score > sampling_best_score){
                sampling_best_score = sampling_score;
                best_ret = ret;
                best_s = s;
            }
        }
        if (move_limit - (100 * K - best_s.action_count_limit) < 0 || sampling_best_score < score){
            // cout << move_limit - (100 * K - best_s.action_count_limit) << endl;
            // cout << sampling_best_score << ", " <<  score << endl;
            // cout << spend_time << endl;
            // cout << interval << endl;
            // cout << spend_time + 1.1*interval << endl;
            // FILE *fp = NULL;
            // fp = fopen("./scores/scores.txt", "a");
            // fprintf(fp, "%d\n", score);
            // fclose(fp);
            break;
        }
        field = extract_used(N, best_s.field);
        move_limit -= best_ret.move.size();
        score = sampling_best_score;
        rets.push_back(best_ret);
        all_print_answer(rets);
        // cout << "move_limit " << move_limit << endl;
        // cout << "score " << score << endl;
        // cout << spend_time << endl;
        // cout << interval << endl;
        // cout << spend_time + 1.1*interval << endl;
        // cout << "--------------キリトリ----------------------" << endl;
        gettimeofday(&end, NULL);
        double spend_time = (end.tv_sec + end.tv_usec / 1e6) - (start.tv_sec + start.tv_usec / 1e6);
        double interval = (end.tv_sec + end.tv_usec / 1e6) - (mid.tv_sec + mid.tv_usec / 1e6);
        if (spend_time + 1.1*interval > 3.0) {
            // FILE *fp = NULL;
            // fp = fopen("./scores/scores.txt", "a");
            // fprintf(fp, "%d\n", score);
            // fclose(fp);
            break;
        }
    }
    
    all_print_answer(rets);

    // gettimeofday(&end, NULL);
    // double spend_time = (end.tv_sec + end.tv_usec / 1e6) - (start.tv_sec + start.tv_usec / 1e6);
    // cout << spend_time << endl;
    return 0;
}
