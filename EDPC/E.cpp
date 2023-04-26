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


int main() {
    int n, limit_w;
    cin >> n >> limit_w;
    vi w(n), v(n);
    rep(i,n) cin >> w[i] >> v[i];
    const int max_v = 1e5;
    const int inf = 1e18;
    vi dp(max_v + 1, inf);
    dp[0] = 0;
    rep(i,n){
        rrep(j, max_v + 1){
            if (j - v[i] < 0) break;
            dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    ll ans = 0;
    rep(i,max_v + 1){
        if (dp[i] <= limit_w) ans = max(ans, i);
    }
    cout << ans << endl;
}