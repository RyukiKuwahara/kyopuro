#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define p pair<ll, ll>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    ll N, A, B;
    cin >> N >> A >> B;
    ll P, Q, R, S;
    cin >> P >> Q >> R >> S;
    ll n = Q - P + 1, m = S - R + 1;

    ll a, b, c, d;
    c = max(1 - A, 1 - B);
    d = min(N - A, N - B);
    a = max(1 - A, B - N);
    b = min(N - A, B - 1);

    vector<vector<char>> vec(n, vector<char>(m, '.'));
    rep(i,n){
        if (-b <= (A - P) - i &&
        (A - P) - i <= -a &&
        0 <= B - R + (A - P) - i &&
        B - R + (A - P) - i <= S - R){
            vec[i][B - R + (A - P) - i] = '#';
        }
        // printf("%d <= %d\n", -b, (A - P) - i);
        // printf("%d <= %d\n", (A - P) - i, -a);
        // printf("%d <= %d\n", 0, B - R + (A - P) - i);
        // printf("%d <= %d\n\n", B - R + (A - P) - i, S - R);

        if (c <= -(A - P) + i &&
        -(A - P) + i <= d &&
        0 <= B - R - (A - P) + i &&
        B - R - (A - P) + i <= S - R){
            vec[i][B - R - (A - P) + i] = '#';
        }
        // printf("%d <= %d\n", c, -(A - P) + i);
        // printf("%d <= %d\n", -(A - P) + i, d);
        // printf("%d <= %d\n", 0, B - R - (A - P) + i);
        // printf("%d <= %d\n\n", B - R - (A - P) + i, S - R);
    }

    rep(i,n){
        rep(j,m){
            cout << vec[i][j];
        }
        cout << endl;
    }
}