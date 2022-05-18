#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

int main() {
    int n, q;
    cin >> n >> q;

    vi front(n+1), back(n+1);
    rep(i,q){
        int num;
        int x, y;
        cin >> num;

        if (num == 1){
            cin >> x >> y;
            back[x] = y;
            front[y] = x;
        } else if (num == 2){
            cin >> x >> y;
            back[x] = 0;
            front[y] = 0;
        } else {
            cin >> x;
            while (front[x] != 0){
                x = front[x];
            }
            vi ans;
            int cnt = 1;
            ans.push_back(x);
            while (back[x] != 0){
                ans.push_back(back[x]);
                cnt++;
                x = back[x];
            }
            printf("%d ", cnt);
            for (auto ele : ans){
                printf("%lld ", ele);
            }
            cout << endl;
        }

        // for (auto ele : front){
        //     printf("%lld ", ele);
        // }
        // cout << endl;
    }
}