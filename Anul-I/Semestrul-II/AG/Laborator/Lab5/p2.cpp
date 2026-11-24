#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    long long flow;
    long long cap;
    int rev;
};

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<Edge>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        long long c;
        fin >> u >> v >> c;
        adj[u].push_back({v, 0, c, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
    }

    int s = 0, t = V - 1;
    vector<int> h(V, 0);
    vector<long long> e(V, 0);
    h[s] = V;

    queue<int> active;
    vector<bool> in_queue(V, false);

    auto enqueue = [&](int v) {
        if (!in_queue[v] && v != s && v != t) {
            active.push(v);
            in_queue[v] = true;
        }
    };

    for (auto& edge : adj[s]) {
        long long f = edge.cap;
        if (f > 0) {
            edge.flow += f;
            adj[edge.to][edge.rev].flow -= f;
            e[edge.to] += f;
            e[s] -= f;
            enqueue(edge.to);
        }
    }

    while (!active.empty()) {
        int u = active.front();
        active.pop();
        in_queue[u] = false;

        for (auto& edge : adj[u]) {
            if (e[u] == 0) break;
            if (edge.cap - edge.flow > 0 && h[u] == h[edge.to] + 1) {
                long long f = min(e[u], edge.cap - edge.flow);
                edge.flow += f;
                adj[edge.to][edge.rev].flow -= f;
                e[u] -= f;
                e[edge.to] += f;
                enqueue(edge.to);
            }
        }
        
        if (e[u] > 0) {
            int min_h = 2 * V;
            for (auto& edge : adj[u]) {
                if (edge.cap - edge.flow > 0) {
                    min_h = min(min_h, h[edge.to]);
                }
            }
            h[u] = min_h + 1;
            enqueue(u);
        }
    }

    fout << e[t] << "\n";
    return 0;
}
