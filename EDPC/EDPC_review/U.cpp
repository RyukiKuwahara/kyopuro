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
    int n;
    cin >> n;
    vvi a(n, vi(n));
    rep(i,n)rep(j,n) cin >> a[i][j];
    int n2 = 1 << n;
    vi comb_a(n2);
    rep(i,n2){
        rep(j,n-1){
            if (!(1<<j&i)) continue;
            REP(k,j+1,n){
                if (!(1<<k&i)) continue;
                comb_a[i] += a[j][k];
            }
        }
    }
    map<ll, ll> mp;
    const ll inf = 1e18;
    vi dp(n2, -inf);
    dp[0] = 0;
    rep(i,n2){
        for (int j=i; j>=0; j--){
            j = j&i;
            dp[i] = max(dp[i], dp[i-j] + comb_a[j]);
            int num = 0;
            rep(k,n) num += (i>>k&1) * pow(3, k);
            rep(k,n) num += (j>>k&1) * pow(3, k);
            mp[num]++;
        }
    }
    for (auto p : mp){
        cout << p.first << " " << p.second << endl;
    }
    cout << dp[n2-1] << endl;
}