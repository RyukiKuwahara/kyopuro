#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll, ll>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int roup_flag = false;
vector<bool> used;
vvi G;

void dfs(int v, int p, int s){
    used[v] = true;
    for (auto nv : G[v]){
        if (nv != p && nv == s) roup_flag = true;
        if (used[nv]) continue;
        dfs(nv, v, s);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    G.resize(n);
    used.resize(n, false);
    rep(i,m){
        int a, b;
        cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    int cnt = 0;
    rep(i,n){
        if (G[i].size() > 2){
            cout << "No" << endl;
            return 0;
        }
        if (G[i].size() <= 1) cnt++;

        dfs(i, -1, i);
    }

    cout << (cnt >= 2 && roup_flag == false ? "Yes" : "No") << endl;
}