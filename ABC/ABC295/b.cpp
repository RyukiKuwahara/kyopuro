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

void destroy(int ii, int jj, int x, vector<string> &vec){
    int r = vec.size();
    int c = vec[0].size();
    rep(i,r){
        rep(j,c){
            if ('1' <= vec[i][j]  && vec[i][j] <= '9') continue;
            if (abs(ii-i) + abs(jj-j) <= x) vec[i][j] = '.';
        }
    }
    vec[ii][jj] = '.';
}

int main() {
    int r, c;
    cin >> r >> c;
    vector<string> vec(r);
    rep(i,r) cin >> vec[i];
    rep(i,r){
        rep(j,c){
            if ('1' <= vec[i][j]  && vec[i][j] <= '9'){
                int x = vec[i][j] - '0';
                destroy(i, j, x, vec);
            }
        }
    }
    rep(i,r) cout << vec[i] << endl;
}