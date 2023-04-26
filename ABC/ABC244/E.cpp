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

int main() {
    ll n, m, k, s, t, x;
    cin >> n >> m >> k >> s >> t >> x;
    s--; t--; x--;
    vvi G(n);
    rep(i,m){
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vvvi dp(k+1, vvi(n, vi(2)));
    dp [0][s][0] = 1;
    const ll mod = 998244353;
    rep(i,k){
        rep(j,n){
            for (auto nv : G[j]){
                if (nv == x){
                    dp[i+1][nv][1] += dp[i][j][0];
                    dp[i+1][nv][0] += dp[i][j][1];
                } else {
                    dp[i+1][nv][0] += dp[i][j][0];
                    dp[i+1][nv][1] += dp[i][j][1];
                }
                dp[i+1][nv][0] %= mod;
                dp[i+1][nv][1] %= mod;
            }
        }
    }
    cout << dp[k][t][0] << endl;
}