#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

int main() {
    int n;
    cin >> n;
    vi dp(n);

    rep(i,n){
        int t, k;
        dp[i] += t;
        rep(j,k){
            int a;
            cin >> a;
            a--;
            dp[i] += dp[a];
        }
    }
    cout << dp[n-1] << endl;
}