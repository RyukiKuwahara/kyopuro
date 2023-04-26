#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define rrep(i, n) for (ll i = (ll)(n-1); i >= 0; i--) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll, ll>
#define ALL(a) a.begin(), a.end()

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}

vi dp;
struct BIT {
    vi bit;
    BIT(){
        bit.resize(1<<20);
    }
    ll get_max (int ind){
        ind++;
        ll res = 0;
        while (ind){
            res = max(res, bit[ind]);
            ind -= -ind & ind;
        }
        return res;
    }
    void update (int ind, ll val){
        ind++;
        while (ind < (1<<20)){
            bit[ind] = max(bit[ind], val);
            ind += -ind & ind;
        }
    }
};

int main() {
    int n;
    cin >> n;
    dp.resize(n);
    vector<P> vec(n);
    rep(i,n){
        int h;
        cin >> h;
        vec[i] = P(h, i);
    }
    sort(ALL(vec));
    vi a(n);
    rep(i,n) cin >> a[i];
    BIT bit;
    ll ans = 0;
    for (auto p : vec){
        int i = p.second;
        dp[i] = bit.get_max(i-1) + a[i];
        bit.update(i, dp[i]);
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}