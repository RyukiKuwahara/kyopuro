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

char convert(char c){
    return char('a' + (c - '0'));
}

bool is_connected(char c){
    return int(c) >= 97 && int(c) <= 102;
}

struct Solver {
    int DR[4] = {0, 1, 0, -1};
    int DC[4] = {1, 0, -1, 0};

    int N, K;
    int action_count_limit;
    mt19937 engine;
    vector<string> field;
    vector<vector<bool>> is_passed;
    vector<vector<bool>> is_placed;

    Solver(int N, int K, const vector<string> &field, int seed = 0) : 
        N(N), K(K), action_count_limit(K * 100), field(field)
    {
        engine.seed(seed);
        is_passed = vector<vector<bool>>(N, vector<bool>(N, false));
        is_placed = vector<vector<bool>>(N, vector<bool>(N, false));
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

    ConnectAction line_fill(int row, int col, int dir, char used)
    {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while (0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if (field[nrow][ncol] == field[row][col]) {
                return ConnectAction(row, col, nrow, ncol);
            }
            assert(field[nrow][ncol] == '0');
            field[nrow][ncol] = used;
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
                if (field[i][j] != '0' && !is_connected(field[i][j])) {
                    for (int dir = 0; dir < 2; dir++) {
                        if (can_connect(i, j, dir)) {
                            ret.push_back(line_fill(i, j, dir, convert(field[i][j])));
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

    pair<int, int> select_highest_variance_parent(vector<ConnectAction> connects){
        UnionFind uf;
        for (auto r : connects) {
            pair<int, int> p1(r.c1_row, r.c1_col), p2(r.c2_row, r.c2_col);
            uf.unite(p1, p2);
        }
        vector<pair<int, int>> computers;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] != '0' and !is_connected(field[i][j])) {
                    computers.emplace_back(i, j);
                }
            }
        }
        map<pair<int,int>, pair<int,int>> same_parent_sum;
        map<pair<int,int>, int> same_parent_num;
        for (auto ele : computers){
            same_parent_sum[uf.find(ele)].first += ele.first;
            same_parent_sum[uf.find(ele)].second += ele.second;
            same_parent_num[uf.find(ele)]++;
        }
        map<pair<int,int>, pair<int,int>> same_parent_ave;
        for (auto ele : same_parent_sum){
            pair<int, int> parent = uf.find(ele.first);
            same_parent_ave[parent].first = same_parent_sum[parent].first /  same_parent_num[parent];
            same_parent_ave[parent].second = same_parent_sum[parent].second /  same_parent_num[parent];
        }
        map<pair<int,int>, int> same_parent_variance;
        for (auto ele : computers){
            pair<int, int> parent = uf.find(ele);
            same_parent_variance[parent] += pow(same_parent_ave[parent].first - ele.first, 2) + pow(same_parent_ave[parent].second - ele.second, 2);
        }
        for (auto &ele : same_parent_variance){
            ele.second /= same_parent_num[uf.find(ele.first)];
        }
        int highest_variance = 0;
        pair<int, int> highest_variance_parent = pair<int, int>(0, 0);
        for (auto ele : same_parent_variance){
            if (ele.second > highest_variance){
                highest_variance_parent = ele.first;
                highest_variance = ele.second;
            }
        }
        // printf("%d %d\n", highest_variance_parent.first, highest_variance_parent.second);
        return highest_variance_parent;
    }

    void dfs(int i, int j, char pc, vector<MoveAction> &add_moves, int ind = -1, vector<pair<int, int>> log = {}){
        is_passed[i][j] = true;
        // cout << i << " " << j << endl;
        if (field[i][j] == pc){
            int x = i, y = j;
            for (int i = log.size() - 1; i >= 0; i--){
                if (abs(x - log[i].first) + abs(y - log[i].second) == 1 and field[log[i].first][log[i].second] != pc){
                    swap(field[x][y], field[log[i].first][log[i].second]);
                    add_moves.emplace_back(x, y, log[i].first, log[i].second);
                    action_count_limit--;
                    x = log[i].first;
                    y = log[i].second;
                }
            }
            is_placed[x][y] = true;
            log.emplace_back(i, j);
            for (int k = 0; k < 4; k++){
                int ni = i + DR[k];
                int nj = j + DC[k];
                if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
                if (is_passed[ni][nj]) continue;
                if (field[ni][nj] != pc and field[ni][nj] != convert(pc)) continue;
                dfs(ni, nj, pc, add_moves, k, log);
            }
        } else {
            int ni = i + DR[ind];
            int nj = j + DC[ind];
            if (ni < 0 || ni >= N || nj < 0 || nj >= N) return;
            if (is_passed[ni][nj]) return;
            if (field[ni][nj] != pc and field[ni][nj] != convert(pc)) return;
            log.emplace_back(i, j);
            dfs(ni, nj, pc, add_moves, ind, log);
        }
    }

    vector<MoveAction> pack(vector<ConnectAction> connects){
        pair<int, int> highest_variance_parent = select_highest_variance_parent(connects);
        // for (auto ele : field){
        //     cout << ele << endl;
        // }
        // cout << endl;
        int i = highest_variance_parent.first;
        int j = highest_variance_parent.second;
        vector<MoveAction> add_moves = {};
        dfs(i, j, field[i][j], add_moves);
        return add_moves;
        // cout << "-----------cut-------------" << endl;
    }

    Result solve()
    {
        // create random moves
        auto moves = move();
        // from each computer, connect to right and/or bottom if it will reach the same type
        int before_action_count_limit = action_count_limit;
        auto connects = connect();
        int after_action_count_limit = action_count_limit;
        action_count_limit += before_action_count_limit - after_action_count_limit;
        // pack the most dispersed group
        auto add_moves = pack(connects);
        for (auto ele : add_moves){
            moves.emplace_back(ele);
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if (is_connected(field[i][j])) field[i][j] = '0';
            }
        }
        // // again, from each computer, connect to right and/or bottom if it will reach the same type
        connects = connect();
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
            if (is_connected(field[i][j])) field[i][j] = '0';
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
        const int sampling = 100;
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
            FILE *fp = NULL;
            fp = fopen("scores.txt", "a");
            fprintf(fp, "%d\n", score);
            fclose(fp);
            break;
        }
        field = extract_used(N, best_s.field);
        move_limit -= best_ret.move.size();
        score = sampling_best_score;
        rets.push_back(best_ret);
        all_print_answer(rets);
        gettimeofday(&end, NULL);
        double spend_time = (end.tv_sec + end.tv_usec / 1e6) - (start.tv_sec + start.tv_usec / 1e6);
        double interval = (end.tv_sec + end.tv_usec / 1e6) - (mid.tv_sec + mid.tv_usec / 1e6);
        if (spend_time + 1.1*interval > 3.0) {
            FILE *fp = NULL;
            fp = fopen("scores.txt", "a");
            fprintf(fp, "%d\n", score);
            fclose(fp);
            break;
        }
        // cout << "move_limit " << move_limit << endl;
        // cout << "score " << score << endl;
        // cout << spend_time << endl;
        // cout << interval << endl;
        // cout << spend_time + 1.1*interval << endl;
        // cout << "--------------キリトリ----------------------" << endl;
    }
    
    all_print_answer(rets);

    // gettimeofday(&end, NULL);
    // double spend_time = (end.tv_sec + end.tv_usec / 1e6) - (start.tv_sec + start.tv_usec / 1e6);
    // cout << spend_time << endl;
    return 0;
}
