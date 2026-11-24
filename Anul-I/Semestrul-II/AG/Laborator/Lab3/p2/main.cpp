#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge& other) const {
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
};

vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj, int src) {
    int V = adj.size();
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    vector<long long> dist(V, INF);

    dist[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        long long d = top.first;
        int u = top.second;

        if (d > dist[u])
            continue;

        for (auto &p : adj[u]) {
            int v = p.first;
            long long w = p.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    fin >> V >> E;

    vector<Edge> edges;
    for (int i = 0; i < E; i++) {
        int x, y;
        long long w;
        fin >> x >> y >> w;
        edges.push_back({x, y, w});
    }

    vector<long long> h(V, 0);
    bool negative_cycle = false;

    for (int i = 0; i < V; i++) {
        for (const auto& edge : edges) {
            if (h[edge.u] + edge.w < h[edge.v]) {
                h[edge.v] = h[edge.u] + edge.w;
            }
        }
    }

    for (const auto& edge : edges) {
        if (h[edge.u] + edge.w < h[edge.v]) {
            negative_cycle = true;
            break;
        }
    }

    if (negative_cycle) {
        fout << "-1\n";
        return 0;
    }

    vector<vector<pair<int, long long>>> adj(V);
    for (auto& edge : edges) {
        edge.w = edge.w + h[edge.u] - h[edge.v];
        adj[edge.u].push_back({edge.v, edge.w});
    }

    sort(edges.begin(), edges.end());

    for (const auto& edge : edges) {
        fout << edge.u << " " << edge.v << " " << edge.w << "\n";
    }

    for (int i = 0; i < V; i++) {
        vector<long long> dist = dijkstra(adj, i);
        for (int j = 0; j < V; j++) {
            if (dist[j] == INF) {
                fout << "INF ";
            } else {
                fout << dist[j] - h[i] + h[j] << " ";
            }
        }
        fout << "\n";
    }

    return 0;
}