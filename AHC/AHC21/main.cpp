#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

struct Ball {
    int x, y;
    int value;
};

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
vector<Ball> balls(max_size);

void print(){
    int ind = 0;
    for (int i=0; i<max_n; i++){
        for (int j=0; j<=i; j++){
            printf("%4d", balls[ind].value);
            ind++;
        }
        cout << endl;
    }
}

void input_data(){
    int ind = 0;
    for (int i=0; i<max_n; i++){
        for (int j=0; j<=i; j++){
            cin >> balls[ind].value;
            balls[ind].x = i;
            balls[ind].y = j;
            ind++;
        }
    }
    // ind = 0;
    // for (int i=0; i<max_n; i++){
    //     for (int j=0; j<=i; j++){
    //         printf("%4d", balls[ind].value);
    //         ind++;
    //     }
    //     cout << endl;
    // }
}

bool compare_by_value(const Ball& a, const Ball& b) {
    return a.value < b.value;
}

void greedy(int from_x, int from_y, int to_x, int to_y){
    while (from_y != to_y){
        Ans a(from_x, from_y, from_x, from_y);
        if (from_y > to_y){
            from_y--;
        } else {
            from_y++;
        }
        a.to_y = from_y;
        ans.push_back(a);
        // cout << "aa" << endl;
    }
    while (from_x > to_x){
        Ans a(from_x, from_y, from_x, from_y);
        from_x--;
        a.to_x = from_x;
        ans.push_back(a);
        // cout << "bb" << endl;
    }
}

void solve(){
    int ind = 0;
    for (int i=0; i<max_n; i++){
        for (int j=0; j<=i; j++){
            greedy(balls[ind].x, balls[ind].y, i, j);
            // fprintf(stderr, "%d %d %d %d\n", balls[ind].x, balls[ind].y, i, j);
            ind++;
        }
    }
    int n = ans.size();
    cout << n << endl;
    rep(i,n) {
        printf("%d %d %d %d\n", ans[i].from_x, ans[i].from_y, ans[i].to_x, ans[i].to_y);
    }
}



int main() {
    input_data();
    // sort(balls.begin(), balls.end(), compare_by_value);
    // for (auto ele : balls){
    //     fprintf(stderr, "%d %d %d\n", ele.value, ele.x, ele.y);
    // }
    solve();
}