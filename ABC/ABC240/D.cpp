#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define rrep(i, n) for (ll i = (ll)(n-1); i >= 0; i--) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define P pair<ll, ll>
#define ALL(a) a.begin(), a.end()
#define rALL(a) a.rbegin(), a.rend()

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

vi a, dp, balls;
void update(ll x, ll y, ll z){
    a.push_back(x);
    dp.push_back(y);
    balls.push_back(z);
}

int main() {
    ll n;
    cin >> n;
    rep(i,n){
        ll x;
        cin >> x;
        if (i == 0){//初期化
            update(x, 1, 1);
            continue;
        }

        if (a.back() != x){
            update(x, 1, balls.back() + 1);
        } else {
            if (dp.back() + 1 == x){
                rep(j,x-1){
                    a.pop_back();
                    dp.pop_back();
                }
                balls.push_back(balls.back() - (x - 1));
            } else {
                update(x, dp.back()+1, balls.back()+1);
            }
        }
        // print(a);
        // printf("%d %d %d\n", a.back(), dp.back(), balls.back());
        cout << balls.back() << endl;
        // cout << endl;
    }
}