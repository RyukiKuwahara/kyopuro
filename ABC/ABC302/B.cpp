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
    int h, w;
    cin >> h >> w;
    vector<string> field(h);
    rep(i,h) cin >> field[i];
    vi dx = {0, 0, 1, -1, 1, -1, 1, -1};
    vi dy = {1, -1, 0, 0, 1, -1, -1, 1};

    rep(i,h){
        rep(j,w){
            rep(k,8){
                string s;
                int ni = i, nj = j;
                while (ni >= 0 && nj >= 0 && ni < h && nj < w){
                    s.push_back(field[ni][nj]);
                    ni += dx[k];
                    nj += dy[k];
                    if (s == "snuke"){
                        rep(l,5){
                            cout << i + 1 + dx[k] * l << " " << j + 1 + dy[k] * l << endl;
                        }
                    }
                }
            }
        }
    }
}