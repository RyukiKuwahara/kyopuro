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
#define rALL(a) a.rbegin(), a.rend()

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}



int main() {
    ll n, x;
    cin >> n >> x;
    vi dp(x+1);
    dp[0] = 1;
    rep(i,n){
        ll a, b;
        cin >> a >> b;
        rrep(j,x+1){
            if (!dp[j]) continue;
            if (j + a <= x) dp[j+a] = dp[j];
            if (j + b <= x) dp[j+b] = dp[j];
            dp[j] = 0;
        }
        // for (auto ele : dp){
        //     printf("%d ", ele);
        // }
        // cout << endl;
    }
    cout << (dp[x] ? "Yes" : "No") << endl;
}