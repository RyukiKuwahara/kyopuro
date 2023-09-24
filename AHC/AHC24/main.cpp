#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++) 
#define REP(i, s, n) for (ll i = (s); i < (ll)(n); i++)
#define vi vector<int>
#define vvi vector<vi>
#define P pair<ll, ll>
#define ALL(a) a.begin(), a.end()

const int N = 50, M = 100;
vvi field(N+2, vi(N+2, 0));

void input(){
    REP(i,1,N+1)REP(j,1,N+1) cin >> field[i][j];
}

void output(){
    REP(i,1,N+1){
        REP(j,1,N+1){
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

vvi create_graph(){
    vvi graph(M+1);
    vi dx = {0, 1, 0, -1};
    vi dy = {1, 0, -1, 0};
    //重複込みで，隣接するノードをリストに追加
    rep(i,N+2)rep(j,N+2){
        // printf("i: %d j: %d\n\n", i, j);
        int p = field[i][j];
        rep(k,4){
            int ni = i + dx[k];
            int nj = j + dy[k];
            // printf("ni: %d nj: %d\n", ni, nj);
            
            if (ni < 0 || nj < 0 || ni > N+1 || nj > N+1) continue;
            int c = field[ni][nj];
            if (c == p) continue;
            // printf("p: %d c: %d\n", p, c);
            graph[p].push_back(c);
        }
    }
    //重複を削除
    rep(i,M){
        sort(ALL(graph[i]));
        graph[i].erase(unique(ALL(graph[i])), graph[i].end());
    }

    // rep(i,M){
    //     for (auto ele : graph[i]){
    //         cout << ele << " ";
    //     }
    //     cout << endl;
    // }

    return graph;
}

vector<vector<P>> create_pos(){
    vector<vector<P>> pos(M+1);
    REP(i,1,N+1)REP(j,1,N+1){
        int c = field[i][j];
        pos[c].push_back(P(i,j));
    }
    return pos;
}

vector<P> dfs(int i, int j, int from, int to, vector<P> removed){
    field[i][j] = from;
    removed.push_back(P(i,j));
    vi dx = {0, 1, 0, -1};
    vi dy = {1, 0, -1, 0};
    rep(k,4){
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (field[ni][nj] != to) continue;
        bool flag = true;
        REP(nni,ni-1,ni+2)REP(nnj,nj-1,nj+2){
            if (field[nni][nnj] != from && field[nni][nnj] != to) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        dfs(ni, nj, from, to, removed);
    }
}

void repair(int i, int j, vector<P> removed, vector<P> pos){

}

void solve(){
    //fieldから隣接リストを作成
    vvi graph = create_graph();

    while (true){
        //変更したグリッドをカウンタ―を初期化
        int counter = 0;

        //区の位置のリストを生成
        vector<vector<P>> pos = create_pos();

        queue<P> que;
        for (auto ele : graph[0]){
            que.push(P(0, ele));
        }
        while (!que.empty()){
            P q = que.front();
            que.pop();
            int from = q.first, to = q.second;

            for (P p : pos[to]){
                int i = p.first, j = p.second;
                bool flag_from = false;
                bool flag_to = false;
                REP(ni,i-1,i+2)REP(nj,j-1,j+2){
                        if (ni == i && nj == j) continue;
                        if (!(field[ni][nj] == from || field[ni][nj] == to)) {
                            flag_from = false;
                            goto label;
                        }
                        if (field[ni][nj] == from) flag_from = true;
                        if (field[ni][nj] == to) flag_to = true;
                }
                label:
                if (flag_from && flag_to){
                    vector<P> removed;
                    dfs(i, j, from, to, removed);
                    repair(i, j, removed, pos[to]);
                    break;
                }
            }
        }

        //カウンターが0なら修了する
        if (counter == 0) break;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    input();
    solve();
    output();
}