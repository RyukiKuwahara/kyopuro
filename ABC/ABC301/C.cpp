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

bool check(char c){
    vector<char> vec = {'a', 't', 'c', 'o', 'd', 'e', 'r'};
    bool flag = false;
    int n = vec.size();
    rep(i,n){
        if (c == vec[i]) flag = true;
    }
    return flag;
}


int main() {
    string s, t;
    cin >> s >> t;
    map<char, int> mp_s, mp_t;
    int n = s.size();
    rep(i,n){
        mp_s[s[i]]++;
        mp_t[t[i]]++;
    }

    for (char c = 'a'; c <= 'z'; c++){
        if (mp_s[c] == mp_t[c]) continue;

        if (!check(c)){
            cout << "No" << endl;
            return 0;
        }

        if (mp_s[c] < mp_t[c]){
            mp_s['@'] -= (mp_t[c] - mp_s[c]);
        } else {
            mp_t['@'] -= (mp_s[c] - mp_t[c]);
        }

        if (mp_s['@'] < 0 || mp_t['@'] < 0){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}