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
    string s;
    ll d;
    cin >> s >> d;
    int n = s.size();
    vvvi dp(n+1, vvi(d, vi(2)));
    //dp[i][j][0]がi番目まででs以下
    //dp[i][j][1]がi番目まで同じ
    dp[0][0][1] = 1;
    const ll mod = 1e9 + 7;
    rep(i,n){
        rep(j,d){
            //dp[i][j][0]について配る
            rep(k,10){
                int nj = (j + k) % d;
                dp[i+1][nj][0] += dp[i][j][0];
                dp[i+1][nj][0] %= mod;
            }
            //dp[i][j][1]について配る
            rep(k,s[i]-'0'+1){
                int nj = (j + k) % d;
                if (k == (s[i]-'0')){
                    dp[i+1][nj][1] += dp[i][j][1];
                    dp[i+1][nj][1] %= mod;
                    continue;
                }
                dp[i+1][nj][0] += dp[i][j][1];
            }
        }
    }
    // rep(i,n+1){
    //     rep(j,d){
    //         printf("dp[%d][%d][0]:%d dp[%d][%d][1]:%d\n", i, j, dp[i][j][0], i, j, dp[i][j][1]);
    //     }
    // }
    ll ans = (dp[n][0][0] + dp[n][0][1] + mod - 1) % mod;
    cout << ans << endl;
}