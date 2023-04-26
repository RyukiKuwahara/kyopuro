#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define p pair<ll, ll>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    ll n;
    cin >> n;
    ll ans = 0;
    for (ll i=1; i<10000; i++){
        for (ll j=i; i*j<100000000; j++){
            if (n / (i * j) - j >= 0){
                ans += n / (i * j) - j + 1;
            } else {
                break;
            }
        }
    }
    cout << ans << endl;
}