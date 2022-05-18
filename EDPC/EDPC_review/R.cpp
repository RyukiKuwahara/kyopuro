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

const ll mod = 1e9 + 7;
struct Matrix {
    vvi val;
    Matrix(){
        val.resize(50, vi(50));
    }
};

Matrix operator* (Matrix a, Matrix b){
    int n = a.val.size();
    Matrix c;
    rep(i,n)rep(j,n)rep(k,n){
        c.val[i][j] += a.val[i][k] * b.val[k][j] % mod;
        c.val[i][j] %= mod;
    }
    return c;
}

Matrix matrix_power(Matrix a, ll k){
    if (k == 1) return a;
    Matrix res = matrix_power(a, k/2);
    res = res * res;
    if (k % 2 == 1) res = res * a;
    return res;
}

int main() {
    ll n, k;
    cin >> n >> k;
    Matrix a;
    rep(i,n)rep(j,n) cin >> a.val[i][j];
    Matrix a_k = matrix_power(a, k);
    ll ans = 0;
    rep(i,n)rep(j,n){
        ans += a_k.val[i][j];
        ans %= mod;
    }
    cout << ans << endl;
}