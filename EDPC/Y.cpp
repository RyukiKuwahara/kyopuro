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

vector<P> coordinates;
const ll max_h = 1e5;
const ll max_n = 3e3;
const ll mod = 1e9 + 7;
vvi dp(max_n+1, vi(2));//始点と終点分の+2が必要
vi fact(2*max_h+1, 1);
vi inv(max_h+1, 1);
vi invfact(max_h+1, 1);
void init(void){
    REP(i,1,2*max_h+1){
        fact[i] = fact[i-1] * i % mod;
    }
    // mod/i*i + mod%i == mod(0)
    // mod/i*i == -mod%i
    // i == -mod%i * inv[mod/i]
    // inv[i] == -inv[mod%i] * (mod/i)
    REP(i,2,max_h+1){
        inv[i] = -inv[mod%i] * (mod/i) % mod;
        if (inv[i] < 0) inv[i] += mod;
    }
    REP(i,1,max_h+1){
        invfact[i] = invfact[i-1] * inv[i] % mod;
    }
}
ll nCk(ll n, ll k){
    return fact[n] * invfact[k] % mod * invfact[n-k] % mod;
}
ll get_route_num(P a, P b){
    ll x = b.first - a.first;
    ll y = b.second - a.second;
    if (x < 0 || y < 0) return 0;
    return nCk(x+y, y);
}

int main() {
    ll h, w, n;
    cin >> h >> w >> n;
    coordinates.push_back(P(1, 1));
    rep(i,n){
        int x, y;
        cin >> x >> y;
        coordinates.push_back(P(x, y));
    }
    sort(ALL(coordinates));
    dp[0][0] = 1;
    init();//階乗と逆元と逆元の階乗を初期化
    REP(i,1,n+1){
        rep(j,i){
            ll num = get_route_num(coordinates[j], coordinates[i]);
            dp[i][0] += dp[j][1] * num % mod;
            dp[i][0] %= mod;
            dp[i][1] += dp[j][0] * num % mod;
            dp[i][1] %= mod;
        }
    }
    ll after_events = 0;
    P goal = P(h, w);
    REP(i,1,n+1){
        ll num = get_route_num(coordinates[i], goal);
        after_events -= dp[i][0] * num % mod;
        after_events += dp[i][1] * num % mod;
        after_events %= mod;
    }
    ll all_events = nCk(h+w-2, w-1);
    ll ans = all_events - after_events;
    ans %= mod;
    if (ans < 0) ans += mod;
    cout << ans << endl;
}