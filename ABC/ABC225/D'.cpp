#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

void print(vi vec){
    int n = vec.size();
    cout << n << " ";
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vi front(n+1);
    vi back(n+1);
    rep(i,m){
        ll q;
        cin >> q;
        if (q == 1){
            ll x, y;
            cin >> x >> y;
            back[x] = y;
            front[y] = x;
        } else if (q == 2){
            ll x, y;
            cin >> x >> y;
            back[x] = 0;
            front[y] = 0;
        } else {
            vi vec;
            ll x;
            cin >> x;
            ll pos = x;
            while (pos != 0){
                vec.push_back(pos);
                pos = front[pos];
            }
            reverse(vec.begin(), vec.end());
            pos = back[x];
            while (pos != 0){
                vec.push_back(pos);
                pos = back[pos];
            }
            print(vec);
        }
        // print(front);
        // print(back);
        // cout << endl;
    }
}