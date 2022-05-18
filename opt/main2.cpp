#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vi>

int main() {
    //初期設定
    const int D = 4;
    const int F = 3;
    vi f = {3, 8, 4};
    vvi c = {{4, 1, 2},
            {5, 1, 5},
            {1, 2, 3},
            {3, 4, 5}};
    const int n = 1 << F;
    const int inf = 1e9;
    int ans = inf;
    for (int bit=1; bit<n; bit++){//施設を配置するかをbit全探索
        //開設コスト
        int establish_cost = 0;
        for (int i=0; i<F; i++){
            if ((1<<i)&bit) establish_cost += f[i];
        }
        //輸送コスト
        int transport_cost = 0;
        for (int i=0; i<D; i++){
            int x = inf;
            for (int j=0; j<F; j++){
                if ((1<<j)&bit) x = min(x, c[i][j]);
            }
            transport_cost += x;
        }
        //開設コストと輸送コストの合計が少ないなら更新する
        ans = min(ans, establish_cost + transport_cost);
    }
    cout << ans << endl;
}