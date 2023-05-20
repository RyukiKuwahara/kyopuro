#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}


int main() {
    int n;
    vi vec(n);
    cin >> n;
    rep(i,n) cin >> vec[i];

    vi ans;
    ans.push_back(vec[0]);
    REP(i,1,n){
        int m = ans.size() - 1;
        int val = vec[i] - ans[m];
        if (val > 0){
            for (int j = ans[m] + 1; j <= vec[i]; j++){
                ans.push_back(j);
            }
        } else {
            for (int j = ans[m] - 1; j >= vec[i]; j--){
                ans.push_back(j);
            }
        }
    }
    print(ans);
}