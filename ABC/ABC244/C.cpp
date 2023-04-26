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

int main() {
    int n;
    cin >> n;
    vector<bool> vec(2*n + 2, true);
    cout << 1 << endl;
    vec[1] = false;
    int ind;
    cin >> ind;
    while (ind != 0){
        vec[ind] = false;
        REP(i,1,2*n + 2){
            if (vec[i]){
                cout << i << endl;
                vec[i] = false;
                break;
            }
        }
        cin >> ind;
    }
}