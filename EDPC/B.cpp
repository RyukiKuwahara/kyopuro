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
    int n, k;
    cin >> n >> k;
    vi h(n);
    rep(i,n) cin >> h[i];
    const ll inf = 1e18;
    vi dp(n, inf);
    dp[0] = 0;
    rep(i,n){
        REP(j,1,k+1){
            if (i + j >= n) continue;
            dp[i+j] = min(dp[i+j], dp[i] + abs(h[i]-h[i+j]));
        }
    }
    cout << dp[n-1] << endl;
}