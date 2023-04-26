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
    ll a, b, c, x;
    cin >> a >> b >> c >> x;
    if (x <= a){
        cout << 1 << endl;
    } else if (x > b) {
        cout << 0 << endl;
    } else {
        double ans = (double)c / (b - a);
        printf("%.10f\n", ans);
    }
}