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

vvi vec;
ll ans = 0, x;
void dfs (int i, int j, ll cnt){
    int h = vec.size(), w = vec[i].size();
    // printf("%d %d %d\n", i, j, cnt);
    if (i >= h){
        if (cnt == x) ans++;
        return;
    }
    if (j >= w) return;
    if (cnt <= x / vec[i][j]){
        dfs(i+1, 0, cnt * vec[i][j]);
    }
    dfs(i, j+1, cnt);
}

int main() {
    ll n;
    cin >> n >> x;
    vec.resize(n);
    rep(i,n){
        int l;
        cin >> l;
        vec[i].resize(l);
        rep(j,l) cin >> vec[i][j];
    }
    // for (auto ele : vec){
    //     print(ele);
    // }
    dfs(0, 0, 1);
    cout << ans << endl;
}