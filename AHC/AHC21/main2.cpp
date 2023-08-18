#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<int, int>


struct Ans {
    int from_x, from_y, to_x, to_y;
    Ans(int x1, int y1, int x2, int y2){
        from_x = x1;
        from_y = y1;
        to_x = x2;
        to_y = y2;
    }
};
vector<Ans> ans;
const int max_size = 465;
const int max_n = 30;
const int max_iter = 10000;
vvi field(max_n, vi(max_n));


void input_data(){
    int ind = 0;
    for (int i=0; i<max_n; i++){
        for (int j=0; j<=i; j++){
            cin >> field[i][j];
        }
    }
    // for (int i=0; i<max_n; i++){
    //     for (int j=0; j<=i; j++){
    //         fprintf(stderr, "%4d", field[i][j]);
    //     }
    //     cout << endl;
    // }
}


// void greedy(int from_x, int from_y, int to_x, int to_y){
//     while (from_y != to_y){
//         if (ans.size() >= max_iter) return;
//         Ans a(from_x, from_y, from_x, from_y);
//         if (from_y > to_y){
//             swap(field[from_x][from_y], field[from_x][from_y-1]);
//             from_y--;
//         } else {
//             swap(field[from_x][from_y], field[from_x][from_y+1]);
//             from_y++;
//         }
//         a.to_y = from_y;
//         ans.push_back(a);
//     }
//     while (from_x > to_x){
//         if (ans.size() >= max_iter) return;
//         Ans a(from_x, from_y, from_x, from_y);
//         swap(field[from_x][from_y], field[from_x-1][from_y]);
//         from_x--;
//         a.to_x = from_x;
//         ans.push_back(a);
//     }
// }

void greedy2(int from_x, int from_y, int to_x, int to_y){

    while (from_x > to_x + 1 && from_y > to_y){
        if (ans.size() >= max_iter) return;
        Ans a(from_x, from_y, from_x, from_y);
        swap(field[from_x][from_y], field[from_x-1][from_y-1]);
        from_x--;
        from_y--;
        a.to_x = from_x;
        a.to_y = from_y;
        ans.push_back(a);
    }

    while (from_y != to_y){
        if (ans.size() >= max_iter) return;
        Ans a(from_x, from_y, from_x, from_y);
        if (from_y > to_y){
            swap(field[from_x][from_y], field[from_x][from_y-1]);
            from_y--;
        } else {
            swap(field[from_x][from_y], field[from_x][from_y+1]);
            from_y++;
        }
        a.to_y = from_y;
        ans.push_back(a);
    }
    while (from_x > to_x){
        if (ans.size() >= max_iter) return;
        Ans a(from_x, from_y, from_x, from_y);
        swap(field[from_x][from_y], field[from_x-1][from_y]);
        from_x--;
        a.to_x = from_x;
        ans.push_back(a);
    }
}

P find(int value){
    for (int i=0; i<max_n; i++){
        for (int j=0; j<=i; j++){
            if (field[i][j] == value) return {i, j};
        }
    }
    return {-1, -1};
}

int find2(int x_len, int f_y, vi &used){
    int n = used.size();
    int min_ind = -1;
    rep(i,n){
        if (used[i]) continue;
        if (min_ind == -1) min_ind = i;
        int value = max(int(abs(i - f_y) - x_len), 0);
        int min_value = max(int(abs(min_ind - f_y) - x_len), 0);
        if (value < min_value){
            min_ind = i;
        }
    }
    used[min_ind] = 1;
    return min_ind;
}

void solve(){
    int value = 0;
    for (int i=0; i<max_n-1; i++){
        vi used(i+1, false);
        for (int j=0; j<=i; j++){
            P p = find(value);
            int nj = find2(p.first - i, p.second, used);
            // int nj = j;
            greedy2(p.first, p.second, i, nj);
            // fprintf(stderr, "%d %d %d %d\n", p.first, p.second, i, j);
            value++;
        }
    }
}

void output_data(){
    int n = ans.size();
    cout << n << endl;
    rep(i,n) {
        printf("%d %d %d %d\n", ans[i].from_x, ans[i].from_y, ans[i].to_x, ans[i].to_y);
    }
}

int main() {
    input_data();
    solve();
    output_data();
}