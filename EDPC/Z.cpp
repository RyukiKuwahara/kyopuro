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
#define INF 1e9

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

ll calc(P p, ll x){
    return p.first * x + p.second;
}

struct CHT {
    vector<P> f;
    vi to;
    CHT (){}
    ll get(ll x){
        int ind = lower_bound(ALL(to), x) - to.begin();
        return calc(f[ind], x);
    }
    void add(ll a, ll b){
        P new_f = P(a, b);
        if (f.size() == 0){
            f.push_back(new_f);
            return;
        }
        if (calc(new_f, INF) >= calc(f.back(), INF)) return;
        if (calc(new_f, -INF) <= calc(f.front(), -INF)){
            f.clear();
            to.clear();
            f.push_back(new_f);
            return;
        }
        while (to.size()){
            if (calc(new_f, to.back()+1) <= calc(f.back(), to.back()+1)){
                f.pop_back();
                to.pop_back();
            } else {
                break;
            }
        }
        ll ac;
        if (to.size()) ac = to.back() + 1;
        else ac = -INF;
        ll wa = INF;
        while (wa - ac > 1){
            ll wj = (ac + wa) / 2;
            if (calc(f.back(), wj) <= calc(new_f, wj)) ac = wj;
            else wa = wj;
        }
        f.push_back(new_f);
        to.push_back(ac);
    }
};

int main() {
    ll n, c;
    cin >> n >> c;
    vi h(n);
    rep(i,n) cin >> h[i];
    CHT cht;
    vi dp(n);
    cht.add(-2*h[0], h[0]*h[0] + dp[0]);
    REP(i,1,n){
        dp[i] = cht.get(h[i]) + h[i]*h[i] + c;
        cht.add(-2*h[i], h[i]*h[i] + dp[i]);
    }
    cout << dp[n-1] << endl;
}