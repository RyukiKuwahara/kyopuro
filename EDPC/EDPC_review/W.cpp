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

struct SEG {
    vi seg;
    vi maximum;
    SEG (){
        seg.resize(1<<20);
        maximum.resize(1<<20);
    }
    void update(int l, int r, ll a, int pos = 1, int bottom = 1, int top = (1<<19)){
        if (l <= bottom && top <= r) {
            seg[pos] += a;
            return;
        }
        if (r <= bottom || top <= l) return;
        int mid = (bottom + top) / 2;
        update(l, r, a, pos*2, bottom, mid);
        update(l, r, a, pos*2 + 1, mid, top);
        maximum[pos] = max(seg[pos*2] + maximum[pos*2], seg[pos*2 + 1] + maximum[pos*2 + 1]);
        // printf("%d %d\n", pos, maximum[pos]);
    }
    ll get_max(){
        return maximum[1] + seg[1];
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
        seg.update(r, r+1, seg.get_max());
        for (auto p : vec[r]){
            ll l = p.first, a = p.second;
            seg.update(l, r+1, a);
        }
        // printf("%d %d\n", r, seg.get_max());
    }
    cout << seg.get_max() << endl;
}


