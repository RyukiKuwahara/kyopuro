#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

vvi G;
vi mark;
void dfs(int v){
    mark[v] = 1;
    for (auto nv : G[v]){
        if (mark[nv] == 1) continue;
        dfs(nv);
    }
}

int main() {
    int n;
    cin >> n;
    G.resize(n);
    mark.resize(n);
    vi t_i(n);

    rep(i,n){
        int k;
        cin >> t_i[i] >> k;
        rep(j,k){
            int a;
            cin >> a;
            G[i].push_back(--a);
        }
    }
    dfs(n-1);

    for (auto e : mark){
        printf("%d", e);
    }
    cout << endl;

    ll ans = 0;
    for (auto ele : mark){
        if (ele == 1) ans += t_i[ele];
    }
    cout << ans << endl;
}