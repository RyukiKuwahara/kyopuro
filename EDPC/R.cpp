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
#define N 50

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

struct Matrix {
    vvi val;
    Matrix(){
        val.resize(N, vi(N));
    }
};

Matrix operator*(Matrix a, Matrix b){
    Matrix c;
    rep(i,N)rep(j,N)rep(k,N){
        c.val[i][j] += a.val[i][k] * b.val[k][j] % mod;
        c.val[i][j] %= mod;
    }
    return c;
}
const ll mod = 1e9 + 7;


Matrix matrix_power(Matrix a, ll b){
    if (b == 1) return a;
    Matrix res = matrix_power(a, b/2);
    res = res * res;
    if (b % 2 == 1) res = res * a;
    return res;
}


int main() {
    ll n, k;
    cin >> n >> k;
    Matrix a;
    rep(i,n)rep(j,n) cin >> a.val[i][j];
    Matrix a_k = matrix_power(a, k);
    ll ans = 0;
    rep(i,n)rep(j,n) ans = (ans + a_k.val[i][j]) % mod;
    cout << ans << endl;
}