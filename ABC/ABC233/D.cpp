#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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
    ll n, k;
    cin >> n >> k;
    vi a(n);
    rep(i,n) cin >> a[i];
    vi cum_sum(n+1);
    rep(i,n) cum_sum[i+1] = cum_sum[i] + a[i];
    map<ll, ll> mp;
    ll ans = 0;
    rep(i,n+1){
        ans += mp[cum_sum[i]];
        mp[k + cum_sum[i]]++;
    }
    cout << ans << endl;
}