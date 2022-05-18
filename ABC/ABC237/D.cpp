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
    int n;
    string s;
    cin >> n >> s;
    vi ans(n+1);
    int l = 0, r = n;
    rep(i,n){
        if (s[i] == 'L'){
            ans[r--] = i;
        } else {
            ans[l++] = i;
        }
    }
    ans[l] = n;
    print(ans);
}