#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rrep(i, n) for (ll i =(ll)(n-1); i >= 0; i--)
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vd vector<double>
#define vvd vector<vd>
#define vvvd vector<vvd>
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
    vvi dp(n+1, vi(n+1, inf));
    rep(i,n) dp[i][i+1] = 0;
    vvi cost(n+1, vi(n+1));
    rep(l,n){
        cost[l][l+1] = a[l];
        REP(r,l+2,n+1){
            cost[l][r] = cost[l][r-1] + a[r-1];
        }
    }
    REP(w,2,n+1){
        rep(l,n+1){
            int r = l + w;
            if (r > n) break;
            REP(m,l+1,r){
                dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r]  + cost[l][r]);
            }
            // printf("%d %d : %d\n", l, r, dp[l][r]);
        }
    }
    // for (auto ele : dp){
    //     print(ele);
    // }
    cout << dp[0][n] << endl;
}