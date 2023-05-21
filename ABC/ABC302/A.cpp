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
    ll a, b, sho, amari;
    cin >> a >> b;
    sho = a / b;
    amari = a % b;
    ll ans = sho;
    if (amari > 0) ans ++;
    cout << ans << endl;
}