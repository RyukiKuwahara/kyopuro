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

ll modPow(ll a, ll n, ll p) {
  if (n == 0) return 1; // 0乗にも対応する場合
  if (n == 1) return a % p;
  if (n % 2 == 1) return (a * modPow(a, n - 1, p)) % p;
  ll t = modPow(a, n / 2, p);
  return (t * t) % p;
}

int main() {
    ll n;
    cin >> n;
    ll mod = 998244353;
    ll l = 1, r = 9;
    ll ans = 0;
    ll c = modPow(2, mod-2, mod);
    ll number_of_terms;
    while (r < n){
        ll nr = r % mod;
        ll nl = l % mod;
        number_of_terms = nr - nl + 1;
        // if (number_of_terms < 0) number_of_terms += mod;
        ans +=  number_of_terms * (1 + number_of_terms) % mod * c % mod;
        ans %= mod;
        l *= 10;
        r = r * 10 + 9;
    }
    l = l % mod;
    n = n % mod;
    number_of_terms = n - l + 1;
    // if (number_of_terms < 0) number_of_terms += mod;
    ans +=  number_of_terms * (1 + number_of_terms) % mod * c % mod;
    ans %= mod;
    cout << ans << endl;
}