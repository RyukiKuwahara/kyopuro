#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

vvi G;
vi t;
vi used;
vi sums;

void resize(ll n){
    G.resize(n);
    t.resize(n);
    used.resize(n);
    sums.resize(n);
}

ll dfs(ll v){
    used[v] = 1;
    ll sum = 0;
    for(auto nv : G[v]){
        if (used[nv]) continue;
        sum += dfs(nv);
    }
    return sums[v] = sum + t[v];
}

int main() {
    ll n;
    cin >> n;
    resize(n);
    rep(i,n){
        ll k;
        cin >> t[i] >> k;
        rep(j,k){
            ll a;
            cin >> a;
            a--;
            G[i].push_back(a);
        }
    }
    ll ans = dfs(n-1);
    cout << ans << endl;
}