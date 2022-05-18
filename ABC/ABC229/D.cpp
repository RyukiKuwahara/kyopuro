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
    string s;
    int k;
    cin >> s >> k;

    int n = s.size();
    vi a(n);
    rep(i,n) a[i] = s[i] == '.';

    int sum = 0, r = 0;
    ll ans = 0;
    rep(l,n){
        while (r < n && sum + a[r] <= k){
            sum += a[r];
            r++;
        }
        sum -= a[l];
        ans = max(ans, r - l);
        // printf("%d %d %d\n", l, r, ans);
    }
    cout << ans << endl;
}