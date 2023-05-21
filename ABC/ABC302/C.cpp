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
    int n, m;
    cin >> n >> m;
    vector<string> vec(n);
    rep(i,n) cin >> vec[i];
    sort(vec.begin(), vec.end());
    do {
        bool flag = true;
        rep(i,n-1){
            int cnt = 0;
            rep(j,m){
                if (vec[i][j] != vec[i+1][j]) cnt++;
            }
            if (cnt > 1){
                flag = false;
                break;
            }
        }
        if (flag){
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(vec.begin(), vec.end()));

    cout << "No" << endl;
    return 0;
}