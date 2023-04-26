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
    vector<double> p(n);
    rep(i,n) cin >> p[i];
    vector<vector<double>> dp(n+1, vector<double>(n+1));
    dp[0][0] = 1;
    rep(i,n){
        rep(j,n){
            dp[i+1][j] += dp[i][j] * (1 - p[i]);
            dp[i+1][j+1] += dp[i][j] * p[i];
        }
    }
    double ans = 0;
    rep(i,n+1){
        if (i > n / 2) ans += dp[n][i];
    }
    printf("%.18f\n", ans);
}