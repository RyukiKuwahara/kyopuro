#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rrep(i, n) for (ll i =(ll)(n-1); i >= 0; i--)
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vd vector<double>
#define vvd vector<vd>
#define vvvd vector<vvd>
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
    vi cba(3);
    rep(i,n){
        int x;
        cin >> x;
        cba[--x]++;
    }
    vvvd dp(n+2, vvd(n+2, vd(n+2)));
    int a = cba[2], b = cba[1], c = cba[0];
    rep(i,n+1){
        rep(j,n+1){
            rep(k,n+1){
                int ijk = i + j + k;
                if (ijk == 0) continue;
                dp[i][j][k] = (double)n / ijk;
                if (i-1 >= 0) dp[i][j][k] += dp[i-1][j+1][k] * i / ijk;
                if (j-1 >= 0) dp[i][j][k] += dp[i][j-1][k+1] *  j / ijk;
                if (k-1 >= 0) dp[i][j][k] += dp[i][j][k-1] * k / ijk;
            }
        }
    }
    // rrep(i,n+1){
    //     rrep(j,n+1){
    //         rrep(k,n+1){
    //             printf("%d %d %d : %f\n", i, j, k, dp[i][j][k]);
    //         }
    //     }
    // }
    printf("%.10f\n", dp[a][b][c]);
}