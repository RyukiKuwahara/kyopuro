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
    string k;
    ll d;
    cin >> k >> d;
    int n = k.size();
    vvvi dp(n+1, vvi(d, vi(2)));
    dp[0][0][0] = 1;
    const ll mod = 1e9 + 7;
    rep(i,n){
        rep(j,d){
            rep(k,10){
                dp[i+1][(j+k)%d][1] += dp[i][j][1];
                dp[i+1][(j+k)%d][1] %= mod;
            }
            ll n_i = k[i] - '0';
            rep(k,n_i){
                dp[i+1][(j+k)%d][1] += dp[i][j][0];
                dp[i+1][(j+k)%d][1] %= mod;
            }
            dp[i+1][(j+n_i)%d][0] = dp[i][j][0];
        }
    }
    cout << (dp[n][0][0] + dp[n][0][1] + mod - 1) % mod << endl;
}