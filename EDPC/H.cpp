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
    rep(i,n) printf("%3d", vec[i]);
    cout << endl;
}

int h, w;
vector<string> field;
vvi dist;
vi dx = {0, 1};
vi dy = {1, 0};
const ll mod = 1e9 + 7;
ll dfs(int x, int y){
    if (dist[x][y] != -1) return dist[x][y];
    ll res = 0;
    rep(i,dx.size()){
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= h || ny >= w) continue;
        if (field[nx][ny] == '#') continue;
        res = res + dfs(nx, ny);
        res %= mod;
    }
    return dist[x][y] = res;
}


int main() {
    cin >> h >> w;
    field.resize(h);
    dist.resize(h, vi(w, -1));
    dist[h-1][w-1] = 1;
    rep(i,h) cin >> field[i];

    ll ans = dfs(0, 0);
    cout << ans << endl;
}