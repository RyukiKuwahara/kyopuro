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
    int n, m;
    cin >> n >> m;
    
    vvi ga(n, vi(n)), gb(n, vi(n));
    rep(i,m){
        int a, b;
        cin >> a >> b;
        a--; b--;
        ga[a][b] = ga[b][a] = 1;
    }
    rep(i,m){
        int a, b;
        cin >> a >> b;
        a--; b--;
        gb[a][b] = gb[b][a] = 1;
    }
    vi convert(n);
    rep(i,n) convert[i] = i;
    do {
        vvi g = gb;
        rep(i,n)rep(j,n) g[convert[i]][convert[j]] = gb[i][j];
        if (g == ga){
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(ALL(convert)));
    cout << "No" << endl;
}