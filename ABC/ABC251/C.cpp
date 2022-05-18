#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll,ll>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}


int main() {
    ll n;
    cin >> n;
    map<string, ll> mp;
    vector<string> S(n);
    rep(i,n){
        string s;
        ll t;
        cin >> s >> t;
        S[i] = s;
        if (!mp.count(s)){
            mp[s] = t;
        }
    }
    string x;
    ll MAX = -1;
    for (auto ele : mp){
        if (ele.second > MAX){
            x = ele.first;
            MAX = ele.second;
        }
    }
    rep(i,n){
        if (x == S[i]){
            cout << (i+1) << endl;
            return 0;
        }
    }
}