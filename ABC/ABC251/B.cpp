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
    ll n, w;
    cin >> n >> w;
    vi a(n);
    rep(i,n) cin >> a[i];

    set<ll> st;
    rep(i,n){
        if (a[i] <= w) st.insert(a[i]);
    }
    rep(i,n-1)REP(j,i+1,n){
        if (a[i] + a[j] <= w) st.insert(a[i] + a[j]);
    }
    rep(i,n-2)REP(j,i+1,n-1)REP(k,j+1,n){
        if (a[i] + a[j] + a[k] <= w) st.insert(a[i] + a[j] + a[k]);
    }
    cout << st.size() << endl;
}