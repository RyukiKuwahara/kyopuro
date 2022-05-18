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

struct BLOCK {
    ll ws, w, s, v;
    BLOCK (ll a, ll b, ll c){
        ws = a + b;
        w = a;
        s = b;
        v = c;
    }
};

bool operator< (BLOCK a, BLOCK b) {
    return a.ws < b.ws;
}

int main() {
    int n;
    cin >> n;
    vector<BLOCK> vec;
    rep(i,n){
        ll w, s, v;
        cin >> w >> s >> v;
        BLOCK block(w, s, v);
        vec.push_back(block);
    }
    sort(rALL(vec));
    const ll max_s = 1e5 + 10;
    vi dp(max_s);
    rep(i,n){
        ll w = vec[i].w;
        ll s = vec[i].s;
        ll v = vec[i].v;
        rep(j, max_s){
            if (j-w < 0) continue;
            int ind = min(s, j-w);
            dp[ind] = max(dp[ind], dp[j] + v);
        }
        // print(dp);
    }
    ll ans = 0;
    rep(i,max_s) ans = max(ans, dp[i]);
    cout << ans << endl;
}


