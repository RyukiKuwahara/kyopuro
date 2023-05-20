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

bool over_min(string s, ll n){
    int m = s.size();
    rep(i,m){
        if (s[i] == '?') s[i] = '0';
    }
    ll pow_2 = 1;
    rep(i,m-1) pow_2 *= 2;
    ll val = 0;
    rep(i,m){
        if (s[i] == '1') val += pow_2;
        pow_2 /= 2;
    }
    if (val > n) return true;
    else return false;
}

ll greed(string s, ll n){
    int m = s.size();
    ll sum = 0;

    ll pow_2 = 1;
    rep(i,m-1) pow_2 *= 2;
    rep(i,m){
        if (s[i] == '1'){
            sum += pow_2;
        }
        pow_2 /= 2;
    }

    pow_2 = 1;
    rep(i,m-1) pow_2 *= 2;
    rep(i,m){
        if (s[i] == '?'){
            if (sum + pow_2 <= n){
                sum += pow_2;
            }
        }
        pow_2 /= 2;
    }
    return sum;
}


int main() {
    string s;
    ll n;
    cin >> s >> n;

    if (over_min(s, n)){
        cout << -1 << endl;
        return 0;
    }

    ll val = greed(s, n);
    cout << val << endl;
    return 0;
}