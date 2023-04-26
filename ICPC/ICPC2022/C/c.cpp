#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll,ll>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    while (n != 0 || m != 0){
        int l = max(n, m);
        vi sum(l);
        sum[0] = 1;
        REP(i,1,l){
            sum[i] = sum[i-1] + 2 * (i + 1) - 1;
        }
        // print(sum);
        if (n == 0){
            cout << -sum[m - 1] << endl;
            cin >> n >> m;
            continue;
        }
        if (m == 0){
            cout << sum[n - 1] << endl;
            cin >> n >> m;
            continue;
        }
        ll pos = sum[n - 1] - sum[m - 1];
        int i = 2;
        int shou = m / i;
        int amari = m % i;
        ll next = sum[n - i + 1] - sum[shou - 1] * (i - amari) - sum[shou] * amari;
        // printf("pos %d  next %d\n", pos, next);
        // printf("n %d  m %d\n", n, m);
        while (pos < next){
            pos = next;
            // cout << next << endl;
            i++;
            if (n-i+1 < 0) break;
            shou = m / i;
            amari = m % i;
            // printf("shou %d  amari %d\n", shou, amari);
            // printf("%lld %lld %lld\n\n",sum[n - i + 1], sum[shou - 1] * (i - amari), sum[shou] * amari);
            next = sum[n - i + 1] - sum[shou - 1] * (i - amari) - sum[shou] * amari + 1;
        }
        cout << pos << endl;

        cin >> n >> m;
    }
}