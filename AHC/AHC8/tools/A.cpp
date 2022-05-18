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

#define MAX_TURN 300

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}


vi px, py, pt;
vi hx, hy;

void input(){
    int n;
    cin >> n;
    px.resize(n); py.resize(n); pt.resize(n);
    rep(i,n) cin >> px[i] >> py[i] >> pt[i];
    int m;
    cin >> m;
    hx.resize(m); hy.resize(m);
    rep(i,n) cin >> hx[i] >> hy[i];
}

void output(){
    int m = hx.size();
    int n = px.size();
    string s;
    s.resize(m, '.');
    rep(i,MAX_TURN){
        cout << s << endl;
        rep(j, n){
           string t;
           cin >> t; 
        }
    }
}


int main() {
    input();
    output();
}