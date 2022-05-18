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
    int n;
    string s;
    cin >> n >> s;
    const ll mod = 1e9 + 7;
    vvi dp(n, vi(n));
    dp[0][0] = 1;
    REP(i,1,n){
        vi sum(i+1);
        rep(j,i) sum[j+1] = (sum[j] + dp[i-1][j]) % mod;
        rep(j,i+1){
            if (s[i-1] == '<'){
                dp[i][j] = sum[j];
            } else {
                dp[i][j] = sum[i] - sum[j];
            }
        }
    }
    ll ans = 0;
    rep(j,n) ans = (ans + dp[n-1][j]) % mod;
    if (ans < 0) ans += mod;
    cout << ans << endl;
}