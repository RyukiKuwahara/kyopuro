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
    cin >> n;
    vector<string> vec(n);
    rep(i,n) cin >> vec[i];
    vvi tate(n, vi(n+1)), yoko(n, vi(n+1));
    vvi naname1(2*n), naname2(2*n);
    rep(i,n){
        rep(j,n){
            yoko[i][j+1] = yoko[i][j];
            if (vec[i][j] == '#') yoko[i][j+1]++;
        }
    }
    // for (auto ele : yoko){
    //     print(ele);
    // }
    rep(i,n){
        rep(j,n){
            tate[i][j+1] = tate[i][j];
            if (vec[j][i] == '#') tate[i][j+1]++;
        }
    }
    rep(i,n){
        rep(j,n){
            if (naname1[i+j].size() == 0) naname1[i+j].push_back(0);
            naname1[i+j].push_back(naname1[i+j].back());
            if (vec[i][j] == '#') naname1[i+j].back()++;
        }
    }
    reverse(ALL(vec));
    rep(i,n){
        rep(j,n){
            if (naname2[i+j].size() == 0) naname2[i+j].push_back(0);
            naname2[i+j].push_back(naname2[i+j].back());
            if (vec[i][j] == '#') naname2[i+j].back()++;
        }
    }
    bool flag = false;
    rep(i,n){
        REP(j,6,n+1){
            if (yoko[i][j] - yoko[i][j-6] >= 4) flag = true;
        }
    }
    rep(i,n){
        REP(j,6,n+1){
            if (tate[i][j] - tate[i][j-6] >= 4) flag = true;
        }
    }
    rep(i,2*n-2){
        int m = naname1[i].size();
        REP(j,6,m){
            if (naname1[i][j] - naname1[i][j-6] >= 4) flag = true;
        }
    }
    rep(i,2*n-2){
        int m = naname2[i].size();
        REP(j,6,m){
            if (naname2[i][j] - naname2[i][j-6] >= 4) flag = true;
        }
    }
    cout << (flag ? "Yes" : "No") << endl;
}