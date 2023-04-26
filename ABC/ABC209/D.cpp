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

vvi G;
vi ranks;
void dfs(int v, int p, int rank){
    ranks[v] = rank;
    for (auto nv : G[v]){
        if (nv == p) continue;
        dfs(nv, v, rank+1);
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    G.resize(n);
    ranks.resize(n);
    rep(i,n-1){
        int a, b;
        cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(0, -1, 0);
    rep(i,q){
        int c, d;
        cin >> c >> d;
        c--; d--;
        cout << ((ranks[c] + ranks[d]) % 2 == 0 ? "Town" : "Road") << '\n';
    }
}