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

// ll gcd(ll a, ll b){
//     return a % b == 0 ? b : gcd(b, a%b);
// }

int main() {
    int n;
    cin >> n;

    vi x(n), y(n);
    rep(i,n){
        cin >> x[i] >> y[i];
    }

    set<p> st;
    int x1, y1, x2, y2, x3, y3;
    rep(i,n-1){
        x1 = x[i]; y1 = y[i];
        REP(j,i+1,n){
            x2 = x[j]; y2 = y[j];
            x3 = x2 - x1; y3 = y2 - y1;
            int z = gcd(x3, y3);
            x3 /= z; y3 /= z;
            st.insert(p(x3, y3));
            st.insert(p(-x3, -y3));
        }
    }
    // for (auto ele : st){
    //     printf("%lld %lld\n", ele.first, ele.second);
    // }
    cout << st.size() << endl;
}