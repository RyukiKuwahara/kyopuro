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

string s;

string transform(char c){
    if (c == 'A') return "BC";
    if (c == 'B') return "CA";
    if (c == 'C') return "AB";
}

char f(ll t, ll k){
    if (t == 0) return s[k];
    if (k == 0) return 'A' + (s[0] - 'A' + t) % 3;
    char c = f(t-1, k/2);
    string s = transform(c);
    int ind = k % 2;
    return s[ind];
}

int main() {
    ll q;
    cin >> s >> q;
    rep(i,q){
        ll t, k;
        cin >> t >> k;
        cout << f(t, k-1) << endl;
    }
}