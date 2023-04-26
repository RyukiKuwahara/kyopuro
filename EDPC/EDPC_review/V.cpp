#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define rrep(i, n) for (ll i = (ll)(n-1); i >= 0; i--) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define P pair<ll, ll>
#define ALL(a) a.begin(), a.end()

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

vvi G;
vvi dp;
ll mod;
void dfs1(int v, int p = -1){
    ll res = 1;
    for (auto nv : G[v]){
        if (nv == p) continue;
        dfs1(nv, v);
        res *= dp[nv][0];
        res %= mod;
    }
    dp[v][0] = res + 1;
}
void dfs2(int v, int p = -1){
    int n = G[v].size();
    vi l(n+1, 1);
    rep(i,n) {
        int nv = G[v][i];
        l[i+1] = l[i];
        if (nv == p) continue;
        l[i+1] = l[i+1] * dp[nv][0] % mod;
    }
    vi r(n+1, 1);
    rrep(i,n) {
        int nv = G[v][i];
        r[i] = r[i+1];
        if (nv == p) continue;
        r[i] = r[i] * dp[nv][0] % mod;
    }
    rep(i,n){
        int nv = G[v][i];
        if (nv == p) continue;
        ll res = (l[i] * r[i+1]) % mod;
        dp[nv][1] = (dp[v][1] * res + 1) % mod;
        dfs2(nv, v);
    }
}
vi ans;
void dfs3(int v, int p = -1){
    ans[v] = dp[v][1];
    // printf("%d %d  %d\n", v, ans[v], dp[v][1]);
    for (auto nv : G[v]){
        if (nv == p) continue;
        dfs3(nv, v);
        ans[v] = ans[v] * dp[nv][0] % mod;
    }
}

int main() {
    ll n;
    cin >> n >> mod;
    G.resize(n);
    //n頂点に対して，頂点0から見て下から入ってくる数[0]頂点0から見て上から入ってくる数[1]，白[0]黒[1]
    dp.resize(n, vi(2, 1));
    ans.resize(n, 1);
    rep(i,n-1){
        int x, y;
        cin >> x >> y;
        x--; y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(0);
    dfs2(0);
    dfs3(0);
    rep(i,n) cout << ans[i] << endl;
}


