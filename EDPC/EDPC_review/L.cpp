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
    vvi dp(n+1, vi(n+1));
    REP(w,1,n+1){
        rep(l,n+1){
            int r = l + w;
            if (r > n) break;
            if (w % 2 == n % 2){
                dp[l][r] = max(dp[l+1][r] + a[l], dp[l][r-1] + a[r-1]);
            } else {
                dp[l][r] = min(dp[l+1][r] - a[l], dp[l][r-1] - a[r-1]);
            }
        }
    }
    cout << dp[0][n] << endl;
}