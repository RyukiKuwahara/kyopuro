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
    ll n;
    cin >> n;
    vvi a(n, vi(n));
    rep(i,n)rep(j,n) cin >> a[i][j];
    ll n_i = 1 << n;
    vi dp(n_i);
    vi cost(n_i);
    rep(i,n_i){
        rep(j,n-1){
            if (!(1<<j&i))continue;
            REP(k,j+1,n){
                if (!(1<<k&i))continue;
                cost[i] += a[j][k];
            }
        }
    }
    // print(cost);
    rep(i,n_i){
        for (int s=i; s>=0; s--){
            s = s & i;
            dp[i] = max(dp[i], dp[i-s] + cost[s]);
        }
    }
    cout << dp[n_i-1] << endl;
}