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
vi dp1;
ll mod;
void dfs1(int v, int p = -1){
    ll res = 1;
    for (auto nv : G[v]){
        if (nv == p) continue;
        dfs1(nv, v);
        res *= dp1[nv];
        res %= mod;
    }
    dp1[v] = res + 1;
}
vi dp2;
void dfs2(int v, int p = -1){
    if (p == -1) dp2[v] = 1;
    int n = G[v].size();
    vi l(n+1, 1), r(n+1, 1);
    rep(i,n){
        int nv = G[v][i];
        l[i+1] = l[i];
        if (nv == p) continue;
        l[i+1] = l[i+1] * dp1[nv] % mod;
    }
    rrep(i,n){
        int nv = G[v][i];
        r[i] = r[i+1];
        if (nv == p) continue;
        r[i] = r[i] * dp1[nv] % mod;
    }
    rep(i,n){
        int nv = G[v][i];
        if (nv == p) continue;
        ll res = (l[i] * r[i+1]) % mod;
        dp2[nv] = (dp2[v] * res + 1) % mod;
        dfs2(nv, v);
    }
}
vi ans;
void dfs3(int v, int p = -1){
    ans[v] = dp2[v];
    for (auto nv : G[v]){
        if (nv == p) continue;
        ans[v] = ans[v] * dp1[nv] % mod;
        dfs3(nv, v);
    }
}

void resize(int n){
    G.resize(n);
    dp1.resize(n);
    dp2.resize(n);
    ans.resize(n);
}

int main() {
    ll n;
    cin >> n >> mod;
    resize(n);
    rep(i,n-1){
        int x, y;
        cin >> x >> y;
        x--; y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(0);
    // print(dp1);
    dfs2(0);
    // print(dp2);
    dfs3(0);
    rep(i,n){
        cout << ans[i] << '\n';
    }
}