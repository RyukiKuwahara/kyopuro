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
    ll k;
    cin >> s >> k;
    ll l=0, r=0;
    ll cnt = 0;
    while (1){   
        if (r == s.size() - 1) break;
        if (s[r] == '.') cnt++;
        if (cnt == k + 1) {
            r--;
            break;
        }
        r++;
    }
    // printf("%d %d\n", l, r);
    ll ans = r-l+1;
    while (r != s.size() - 1){
        while (s[l] != '.') l++;
        l++;
        ll cnt = 0;
        while (1){
            if (r+1 < s.size() && s[r+1] == '.') cnt++;
            if (cnt == 2) break;
            r++;
            if (r == s.size() - 1) break;
        }
        // printf("%d %d\n", l, r);
        ans = max(ans, r-l+1);
    }
    cout << ans << endl;
}