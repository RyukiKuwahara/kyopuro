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

void print(vector<double> vec){
    int n = vec.size();
    rep(i,n) printf("%5.2f", vec[i]);
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
    // for (auto ele : dp){
    //     print(ele);
    // }
    double ans = 0;
    rep(j,n+1){
        if (j > n / 2) ans += dp[n][j];
    }
    printf("%.18f\n", ans);
}