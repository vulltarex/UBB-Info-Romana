#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, c, d;
    if (!(fin >> n >> c >> d)) return 0;

    int S = n;
    int T = n - 1;
    int total_nodes = n + 1;

    vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));
    vector<vector<int>> adj(total_nodes);

    auto add_edge = [&](int u, int v, int cap) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    };

    for (int i = 0; i < c; ++i) {
        add_edge(S, i, INF);
    }

    for (int i = 0; i < d; ++i) {
        int u, v, cap;
        fin >> u >> v >> cap;
        add_edge(u, v, cap);
    }

    int max_flow = 0;
    vector<int> parent(total_nodes);

    auto bfs = [&]() {
        fill(parent.begin(), parent.end(), -1);
        parent[S] = S;
        queue<pair<int, int>> q;
        q.push({S, INF});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == T) return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    };

    int flow;
    while ((flow = bfs()) > 0) {
        max_flow += flow;
        int cur = T;
        while (cur != S) {
            int prev = parent[cur];
            capacity[prev][cur] -= flow;
            capacity[cur][prev] += flow;
            cur = prev;
        }
    }

    fout << max_flow << "\n";
    for (int i = 0; i < c; ++i) {
        fout << (INF - capacity[S][i]) << (i == c - 1 ? "" : " ");
    }
    fout << "\n";

    return 0;
}
