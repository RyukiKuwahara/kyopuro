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
    const ll a_max = 1e4;
    const ll b_max = 1e6;
    ll cnt = 0;
    REP(i,1,a_max){
        REP(j,i,b_max){
            cnt++;
            if (n / (i * j) - j + 1 < 0) break;
            ans += n / (i * j) - j + 1;
        }
    }
    cout << cnt << endl;
    cout << ans << endl;
}