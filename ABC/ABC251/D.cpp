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


int main() {
    cout << 300 << endl;
    ll x = 1;
    rep(i,3){
        REP(j,1,100){
            cout << j * x << " ";
        }
        x *= 100;
    }
    cout << endl;
}