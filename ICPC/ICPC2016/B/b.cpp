#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<ll>
#define vvi vector<vi>
#define P pair<ll,ll>

void print(vi vec){
    int n = vec.size();
    rep(i,n) cout << vec[i] << " ";
    cout << endl;
}


int main() {
    int n;
    cin >> n;
    while (n != 0){

        if (n == 1){
            char c;
            cin >> c;
            cout << c << " " << 1 << endl;
            cin >> n;
            continue;
        }       
        map<char, int> mp1;
        string s = "";
        rep(i,n){
            char c;
            cin >> c;
            mp1[c]++;
            s.push_back(c);
        }
        int max_vote = -1;
        char ans1 = 'x';
        for (auto ele : mp1){
            if (ele.second > max_vote){
                max_vote = ele.second;
                ans1 = ele.first;
            }
        }
        int cnt = 0;
        for (auto ele : mp1){
            if (ele.second == max_vote) cnt++;
        }
        if (cnt > 1){
            cout << "TIE" << endl;
        }

        cnt = 0;
        map<char, int> mp2;
        int second_vote = 0;
        rep(i,n){
            if (s[i] == ans1) cnt++;
            else {
                mp2[s[i]]++;
                second_vote = max(second_vote, mp2[s[i]]);
            }
            // printf("log %lld %d\n", n - i - 1, cnt - second_vote);
            if (n - i - 1 < cnt - second_vote){
                cout << ans1 << " " << i + 1 << endl;
                break;
            }
        }
        // cout << endl;
        cin >> n;
    }
}