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
    vector<char> s(3);
    rep(i,3) cin >> s[i];
    vector<char> t(3);
    rep(i,3) cin >> t[i];
    int cnt = 0;
    rep(i,3){
        if (s[i] == t[i]) cnt++;
    }
    if (cnt == 0 || cnt == 3) cout << "Yes" << endl;
    else cout << "No" << endl;
}