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
    vi a(n);
    rep(i,n) cin >> a[i];
    const ll inf = 1e18;
    vvi sum(n+1, vi(n+1));
    rep(l,n){
        sum[l][l+1] = a[l];
        REP(r,l+2,n+1){
            sum[l][r] = sum[l][r-1] + a[r-1];
        }
    }
    vvi dp(n+1, vi(n+1));
    REP(w,2,n+1){
        rep(l,n+1){
            int r = l + w;
            if (r > n) break;
            dp[l][r] = inf;
            REP(m,l+1,r){
                dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + sum[l][r]);
            }
        }
    }
    // for (auto ele : dp){
    //     print(ele);
    // }
    cout << dp[0][n] << endl;
}