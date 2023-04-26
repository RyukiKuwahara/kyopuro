#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define p pair<ll, ll>
#define ALL(vec) vec.begin(),vec.end()

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vvi ab(n), cd(n);
    rep(i,m){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        ab[a].push_back(b);
        ab[b].push_back(a);
    }
    rep(i,m){
        ll c, d;
        cin >> c >> d;
        c--; d--;
        cd[c].push_back(d);
        cd[d].push_back(c);
    }

    vi convert(n);
    rep(i,n){
        convert[i] = i;
    }

    do {
        bool flag = true;
        rep(i,n){
            for(auto v : cd[convert[i]]){
                v = convert[v];
                ll l = ab[i].size();
                rep(j,l){
                    if (v == ab[i][j]) break;
                    if (j == l-1) flag = false;
                }
            }
        }
        if (flag){
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(ALL(convert)));
    cout << "No" << endl;
}