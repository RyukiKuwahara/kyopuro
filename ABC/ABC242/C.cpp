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
    ll n;
    cin >> n;
    vvi dp(n, vi(10));
    const ll mod = 998244353;
    REP(i,1,10) dp[0][i] = 1;
    REP(i,1,n){
        vi sum(11);
        REP(j,1,10) sum[j] = (sum[j-1] + dp[i-1][j]) % mod;
        sum[10] = sum[9];
        REP(j,1,10) {
            dp[i][j] = sum[j+1];
            if (j-2 > 0) dp[i][j] -= sum[j-2];
            dp[i][j] %= mod;
        }
    }
    ll ans = 0;
    REP(i,1,10) ans = (ans + dp[n-1][i]) % mod;
    if (ans < 0) ans += mod;
    cout << ans << endl;
}