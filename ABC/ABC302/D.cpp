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

ll findMaxValue(vi &sortedArray, ll target) {
    int left = 0;
    int right = sortedArray.size() - 1;
    ll result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sortedArray[mid] <= target) {
            result = sortedArray[mid];
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}


int main() {
    ll n, m, d;
    cin >> n >> m >> d;
    vi a(n), b(m);
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll ans = -1;
    rep(i,n){
        ll x = a[i];
        ll y = findMaxValue(b, x+d);
        if (y >= x - d) {
            x += y;
            ans = max(ans, x);
        }
    }
    cout << ans << endl;
}