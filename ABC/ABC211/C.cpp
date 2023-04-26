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


int main() {
    string s;
    cin >> s;
    int n = s.size();
    string t = "chokudai";
    int m = t.size();
    vi vec(n+1);
    vec[0] = 1;
    ll mod = 1e9 + 7;
    rep(i,n){
        rep(j,m){
            if (t[j] == s[i]){
                vec[j+1] = (vec[j+1] + vec[j]) % mod;
            }
        }
    }
    cout << vec[m] << endl;
}