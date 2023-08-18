#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Pos {
    int y, x;
};

struct Judge {
    void set_temperature(const vector<vector<int>>& temperature) {
        for (const vector<int>& row : temperature) {
            for (int i = 0; i < row.size(); i++) {
                cout << row[i] << (i == row.size() - 1 ? "\n" : " ");
            }
        }
        cout.flush();
    }

    int measure(int i, int y, int x) {
        cout << i << " " << y << " " << x << endl; // endl does flush
        int v;
        cin >> v;
        if (v == -1) {
            cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << endl;
            exit(1);
        }
        return v;
    }

    void answer(const vector<int>& estimate) {
        cout << "-1 -1 -1" << endl;
        for (int e : estimate) {
            cout << e << endl;
        }
    }
};

struct Solver {
    const int L;
    const int N;
    const int S;
    const vector<Pos> landing_pos;
    Judge judge;

    Solver(int L, int N, int S, const vector<Pos>& landing_pos) : 
        L(L), N(N), S(S), landing_pos(landing_pos), judge() {
    }

    void solve() {
        const vector<vector<int>> temperature = create_temperature();
        judge.set_temperature(temperature);
        const vector<int> estimate = predict(temperature);
        judge.answer(estimate);
    }

    vector<vector<int>> create_temperature() {
        vector<vector<int>> temperature(L, vector<int>(L, 0));
        // set the temperature to i * 10 for i-th position
        // for (int i = 0; i < N; i++) {
        //     temperature[landing_pos[i].y][landing_pos[i].x] = i * 10;
        // }
        const int center = 750;
        for (int i = 0; i < L; i++){
            for (int j = 0; j < L; j++){
                int distance_x = abs(L/2 - i - 1);
                int distance_y = abs(L/2 - j - 1);
                int distance = distance_x + distance_y;
                temperature[i][j] = center - distance * 10;
            }
        }
        return temperature;
    }

    vector<int> predict(const vector<vector<int>>& temperature) {
        vector<int> estimate(N);
        for (int i_in = 0; i_in < N; i_in++) {
            // you can output comment
            // cout << "# measure i=" << i_in << " y=0 x=0" << endl;

            // int measured_value = judge.measure(i_in, 0, 0);
            // // answer the position with the temperature closest to the measured value
            // int min_diff = 9999;
            // for (int i_out = 0; i_out < N; i_out++) {
            //     const Pos& pos = landing_pos[i_out];
            //     int diff = abs(temperature[pos.y][pos.x] - measured_value);
            //     if (diff < min_diff) {
            //         min_diff = diff;
            //         estimate[i_in] = i_out;
            //     }
            // }

            vector<vector<int>> sum_measured_val(2, vector<int>(2));
            vector<vector<int>> ave_measured_val(2, vector<int>(2));
            vector<int> dx = {-5, 5};
            vector<int> dy = {-5, 5};
            const Pos& pos_in = landing_pos[i_in];

            auto mod = [](int x, int m) {
                return (x + m) % m;
            };

            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 2; j++){
                    for (int k = 0; k < 10; k++){
                        sum_measured_val[i][j] += judge.measure(i_in, dx[i], dy[j]);
                    }
                    ave_measured_val[i][j] = sum_measured_val[i][j] / 10;
                    printf("# ave_measured_val[%d][%d] = %d", i, j, ave_measured_val[i][j]); cout << endl;
                }
            }

            cout << "# hoge" << endl;


            int min_loss = 1e9;
            for (int i_out = 0; i_out < N; i_out++){
                const Pos& pos_out = landing_pos[i_out];
                
                int loss = 0;
                for (int i = 0; i < 2; i++){
                    int ni = mod(pos_out.x + dx[i], L);
                    for (int j = 0; j < 2; j++){
                        int nj = mod(pos_out.y + dy[j], L);
                        loss += abs(temperature[ni][nj] - ave_measured_val[i][j]);
                    }
                }

                if (loss < min_loss){
                    min_loss = loss;
                    estimate[i_in] = i_out;
                    printf("# min_loss : %d  estimate[%d] = %d", min_loss, i_in, i_out); cout << endl;

                }
            }


        }
        return estimate;
    }
};

int main() {
    int L, N, S;
    cin >> L >> N >> S;
    vector<Pos> landing_pos(N);
    for (int i = 0; i < N; i++) {
        cin >> landing_pos[i].y >> landing_pos[i].x;
    }

    Solver solver(L, N, S, landing_pos);
    solver.solve();
}
