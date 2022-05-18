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
    int n;
    cin >> n;
    vvi a(n, vi(n));
    rep(i,n)rep(j,n) cin >> a[i][j];
    int n2 = (1 << n);
    vi dp(n2);
    dp[0] = 1;
    vi bit_cnt(n2);
    const ll mod = 1e9 + 7;
    REP(i,1,n2){
        bit_cnt[i] = bit_cnt[i/2] + i % 2;
        rep(j,n){
            if (!(i>>j&1)) continue;
            dp[i] += dp[i - (1<<j)] * a[bit_cnt[i] - 1][j];
            dp[i] %= mod;
            // cout << i << " " << j << " " << dp[i] << endl;
        }
    }
    // print(dp);
    cout << dp[n2 - 1] << endl;
}