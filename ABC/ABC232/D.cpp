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
    int h, w;
    cin >> h >> w;
    vector<string> field(h);
    rep(i,h) cin >> field[i];
    queue<P> q;
    q.push(P(0, 0));
    vi dx = {0, 1};
    vi dy = {1, 0};
    vvi dist(h, vi(w));
    dist[0][0] = 1;
    while (!q.empty()){
        P p = q.front(); q.pop();
        rep(i,2){
            ll ni = p.first + dx[i], nj = p.second + dy[i];
            if (ni < 0 || nj < 0 || ni >= h || nj >= w) continue;
            if (field[ni][nj] == '#') continue;
            if (dist[p.first][p.second] + 1 > dist[ni][nj]){
                dist[ni][nj] = dist[p.first][p.second] + 1;
                q.push(P(ni, nj));
            } 
        }
    }
    ll ans = 0;
    rep(i,h){
        rep(j,w) {
            ans = max(ans, dist[i][j]);
        }
    }
    cout << ans << endl;
}