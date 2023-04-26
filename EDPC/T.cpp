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
    ll n;
    string s;
    cin >> n >> s;
    const ll mod = 1e9 + 7;
    vvi dp(n, vi(n));
    dp[0][0] = 1;
    REP(i,1,n){
        vi sums(i+1);
        rep(j,i){//i-1の時の累積和
            sums[j+1] = sums[j] + dp[i-1][j];
            sums[j+1] %= mod;
        }
        rep(j,i+1){
            if (s[i-1] == '<'){
                dp[i][j] += sums[j];
                dp[i][j] %= mod;
            } else {
                dp[i][j] += sums[i] - sums[j];
                dp[i][j] %= mod;
            }
        }
    }
    ll ans = 0;
    rep(i,n){
        ans += dp[n-1][i];
        ans %= mod;
    }
    cout << (ans + mod) % mod << endl;
}