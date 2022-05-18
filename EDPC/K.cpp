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
    int n, k;
    cin >> n >> k;
    vi a(n);
    rep(i,n) cin >> a[i];
    vector<bool> dp(k+1, false);
    rep(i,k+1){
        rep(j,n){
            if (i - a[j] < 0) break;
            dp[i] = dp[i] || !dp[i - a[j]];
        }
    }
    cout << (dp[k] == true ? "First" : "Second") << endl;
}