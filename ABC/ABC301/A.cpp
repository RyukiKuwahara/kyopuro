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
    int n;
    string s;
    cin >> n >> s;
    int t = 0, a = 0;
    char ans = 'T';
    rep(i,n){
        if (s[i] == 'T') t++;
        else a++;

        if (t > a) ans = 'T';
        else if (t < a) ans = 'A';
    }
    cout << ans << endl;
}