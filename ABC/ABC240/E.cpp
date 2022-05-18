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

vvi G;
vector<P> ans;
ll cnt = 1;
void dfs(int v, int p = -1){
    ans[v].first = cnt;
    for (auto nv : G[v]){
        if (nv == p) continue;
        dfs(nv, v);
        cnt++;
    }
    if (G[v].size() >= 2) cnt--;
    ans[v].second = cnt;
}

int main() {
    ll n;
    cin >> n;
    G.resize(n);
    ans.resize(n);
    rep(i,n-1){
        ll u, v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    G[0].push_back(-1);
    dfs(0);
    rep(i,n){
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
}