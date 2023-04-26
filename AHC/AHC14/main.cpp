#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll, ll>
#define ALL(a) a.begin(), a.end()

vvi field(vi(61, vi(61, 0)));

struct Point {
    int x, y;
    P up, right, down, left;
};

int main() {
    int n, m;
    cin >> n >> m;
    rep(i,m){
        int x, y;
        cin >> x >> y;
        field[x][y] = 1;
    }
}