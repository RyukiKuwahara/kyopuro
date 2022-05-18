#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define vvvi vector<vvi>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}


int main() {
    ll n;
    cin >> n;
    vi a(n);
    rep(i,n) cin >> a[i];
    const ll inf = 1e18;
    vvvi dp(n, vvi(2, vi(2, inf)));
    //0が一つ次まで，1がその数まで
    dp[0][0][0] = a[0];
    dp[0][0][1] = a[0] + a[n-1];
    dp[0][1][1] = a[n-1];
    REP(i,1,n){
        dp[i][0][0] = min(dp[i-1][0][0] + a[i], dp[i-1][1][0] + a[i]);
        dp[i][1][0] = dp[i-1][0][0];
        dp[i][0][1] = min(dp[i-1][0][1] + a[i], dp[i-1][1][1] + a[i]);
        dp[i][1][1] = dp[i-1][0][1];
    }
    cout << min(min(dp[n-2][0][0], dp[n-1][1][0]), min(dp[n-3][0][1], dp[n-2][1][1])) << endl;
}