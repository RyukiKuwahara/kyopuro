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

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

const ll inf = 1e18;
struct SEG {
    vi sum, mx;
    SEG (){
        sum.resize(1<<19);
        mx.resize(1<<19);
    }
    void add_value (ll l, ll r, ll a, ll pos = 1, ll bottom = 0, ll top = (1<<18)){
        if (l <= bottom && top <= r){
            sum[pos] += a;
            return;
        }
        if (top <= l || r <= bottom){
            return;
        }
        ll mid = (bottom + top) / 2;
        add_value(l, r, a, pos*2, bottom, mid);
        add_value(l, r, a, pos*2+1, mid, top);
        mx[pos] = max(mx[pos*2] + sum[pos*2], mx[pos*2+1] + sum[pos*2+1]);
    }
    ll get_max_value (ll l, ll r, ll pos = 1, ll bottom = 0, ll top = (1<<18)){
        if (l <= bottom && top <= r){
            return sum[pos] + mx[pos];
        }
        if (top <= l || r <= bottom){
            return -inf;
        }
        ll mid = (bottom + top) / 2;
        ll l_num = get_max_value(l, r, pos*2, bottom, mid);
        ll r_num = get_max_value(l, r, pos*2+1, mid, top);
        return max(l_num, r_num) + sum[pos];
    }
};


int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<P>> vec(n+1);
    rep(i,m){
        ll l, r, a;
        cin >> l >> r >> a;
        vec[r].push_back(P(l, a));
    }
    SEG seg;
    REP(r,1,n+1){
        seg.add_value(r, r+1, seg.get_max_value(0, r));
        for (auto p : vec[r]){
            ll l = p.first, a = p.second;
            seg.add_value(l, r+1, a);
        }
    }
    cout << seg.get_max_value(0, n+1) << endl;
}