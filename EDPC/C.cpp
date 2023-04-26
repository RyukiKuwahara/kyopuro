#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
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
    vvi vec(n, vi(3));
    rep(i,n)rep(j,3) cin >> vec[i][j];
    vvi dp(n+1, vi(3));
    rep(i,n){
        rep(j,3){
            rep(k,3){
                if (j == k) continue;
                dp[i+1][k] = max(dp[i+1][k], dp[i][j] + vec[i][k]);
            }
        }
    }
    ll ans = 0;
    rep(i,3) ans = max(ans, dp[n][i]);
    cout << ans << endl;
}