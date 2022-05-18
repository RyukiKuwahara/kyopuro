#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define rrep(i, n) for (ll i = (ll)(n-1); i >= 0; i--) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll, ll>
#define ALL(a) a.begin(), a.end()

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

vvi G;
vi dist;

ll dfs(int v){
    if (dist[v] != -1) return dist[v];
    ll res = 0;
    for (auto nv : G[v]){
        res = max(res, dfs(nv) + 1);
    }
    return dist[v] = res;
}

int main() {
    int n, m;
    cin >> n >> m;
    G.resize(n);
    dist.resize(n, -1);

    rep(i,m){
        int x, y;
        cin >> x >> y;
        x--; y--;
        G[x].push_back(y);
    }

    ll ans = 0;
    rep(i,n){
        ans = max(ans, dfs(i));
    }
    cout << ans << endl;
}