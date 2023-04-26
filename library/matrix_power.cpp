#define N ?//行列のサイズ

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