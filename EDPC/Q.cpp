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

vi bit;
int n;
ll max_val(int ind){
    ind++;
    ll res = 0;
    while (ind){
        res = max(res, bit[ind]);
        ind -= ind & -ind;
    }
    return res;
}

void set_val(int ind, ll val){
    ind++;
    while (ind <= n){
        bit[ind] = max(bit[ind], val);
        ind += ind & -ind;
    }
}


int main() {
    cin >> n;
    bit.resize(n+1);
    vector<P> h(n);
    rep(i,n){
        int hi;
        cin >> hi;
        h[i] = P(hi, i);
    }
    sort(ALL(h));
    vi a(n);
    rep(i,n) cin >> a[i];
    vi dp(n);
    ll ans = 0;
    for (auto p : h){
        int i = p.second;
        dp[i] = a[i];
        dp[i] = max(dp[i], max_val(i-1) + a[i]);
        ans = max(ans, dp[i]);
        set_val(i, dp[i]);
    }
    cout << ans << endl;
}