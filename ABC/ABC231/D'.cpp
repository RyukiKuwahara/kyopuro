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

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    dsu d(n);
    vi G(n);
    rep(i,m){
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (d.same(a, b)){
            cout << "No" << endl;
            return 0;
        } else {
            d.merge(a, b);
            G[a]++;
            G[b]++;
        }
    }
    rep(i,n){
        if (G[i] > 2){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}