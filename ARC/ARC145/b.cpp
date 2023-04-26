#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}


int main() {
    ll n, a, b;
    cin >> n >> a >> b;

    ll ans = 0;
    if (a < b){
        ans += n - a - 1;
        if (ans < 0) ans = 0;
    } else {
        ans += n / a * b;
        if (n % a < b) ans -= b - n % a;
    }
    cout << ans << endl;
}