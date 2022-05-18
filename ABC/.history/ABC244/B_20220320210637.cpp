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

int main() {
    int n;
    string t;
    cin >> n >> t;
    vi dx = {1, 0, -1, 0};
    vi dy = {0, -1, 0, 1};
    int pos = 0;
    int x = 0, y = 0;
    rep(i,n){
        if (t[pos] == 'S'){
            x += dx[pos];
            y += dy[pos];
        } else {
            pos = (pos + 1) % 4;
        }
    }
    printf("%d %d\n", x, y);
}