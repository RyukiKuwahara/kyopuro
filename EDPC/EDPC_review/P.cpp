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
vvi dp;
const ll mod = 1e9 + 7;
void dfs(int v, int p = -1){
    for (auto nv : G[v]){
        if (nv == p) continue;
        dfs(nv, v);
        //0が黒，1が白
        dp[v][0] = dp[v][0] * dp[nv][1] % mod;
        dp[v][1] = dp[v][1] * (dp[nv][0] + dp[nv][1]) % mod;
    }
}


int main() {
    int n;
    cin >> n;
    G.resize(n);
    dp.resize(n, vi(2, 1));
    rep(i,n-1){
        int x, y;
        cin >> x >> y;
        x--; y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(0);
    cout << (dp[0][0] + dp[0][1]) % mod << endl;
}