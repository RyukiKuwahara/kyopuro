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

struct BLOCK{
    ll sum, w, s, v;
    BLOCK(ll a, ll b, ll c){
        sum = a + b;
        w = a;
        s = b;
        v = c;
    }
};

bool operator < (BLOCK a, BLOCK b){
    return a.sum < b.sum;
}

int main() {
    ll n;
    cin >> n;
    vector<BLOCK> vec;
    rep(i,n){
        ll w, s, v;
        cin >> w >> s >> v;
        BLOCK block(w, s, v);
        vec.push_back(block);
    }
    sort(rALL(vec));
    const ll max_s = 1e4;
    vi dp(max_s+1);
    rep(i,n){
        ll w, s, v;
        w = vec[i].w;
        s = vec[i].s;
        v = vec[i].v;
        REP(j,w,max_s+1){
            ll ind = j - w;
            ind = min(ind, s);
            dp[ind] = max(dp[ind], dp[j] + v);
        }
        dp[s] = max(dp[s], v);
    }
    ll ans = 0;
    rep(i,max_s+1){
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}