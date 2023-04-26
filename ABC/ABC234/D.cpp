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

int main() {
    int n, k;
    cin >> n >> k;
    vi p(n);
    rep(i,n) cin >> p[i];
    vector<bool> used(n);
    ll MIN = 1e9;
    rep(i,k){
        used[p[i]] = true;
        MIN = min(MIN, p[i]);
    }
    cout << MIN << endl;
    REP(i,k,n){
        used[p[i]] = true;
        if (p[i] <= MIN){
        } else {
            while (!used[++MIN]){}
        }
        cout << MIN << '\n';
    }
}