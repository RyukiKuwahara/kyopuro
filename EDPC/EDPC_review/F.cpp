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
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    vvi dp(n+1, vi(m+1));
    // rep(i,n){
    //     rep(j,m){
    //         dp[i][j+1] = max(dp[i][j+1], dp[i][j]);
    //         dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
    //         if (s[i] == t[j]) dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+1);
    //     }
    // }
    REP(i,1,n+1){
        REP(j,1,m+1){
            dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            if (s[i-1] == t[j-1]) dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
        }
    }
    // for (auto ele : dp){
    //     print(ele);
    // }
    string ans;
    while (n > 0 && m > 0){
        if (dp[n][m] == dp[n][m-1]){
            m--;
        } else if (dp[n][m] == dp[n-1][m]){
            n--;
        } else {
            n--; m--;
            ans.push_back(s[n]);
        }
    }
    reverse(ALL(ans));
    cout << ans << endl;
}