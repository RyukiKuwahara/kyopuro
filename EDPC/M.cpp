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
    int n, k;
    cin >> n >> k;
    vi a(n);
    rep(i,n) cin >> a[i];
    vvi dp(n+1, vi(k+1));
    dp[0][0] = 1;
    const ll mod = 1e9 + 7;
    REP(i,1,n+1){
        ll sum = 0;
        rep(j,k+1){
            sum += dp[i-1][j];
            sum %= mod;
            dp[i][j] = sum;
            if (j - a[i-1] >= 0) sum -= dp[i-1][j-a[i-1]];
        }
    }
    if (dp[n][k] < 0) dp[n][k] += mod;
    cout << dp[n][k] << endl;
}