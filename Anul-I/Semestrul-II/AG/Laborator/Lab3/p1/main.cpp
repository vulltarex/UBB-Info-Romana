#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<int> dijkstra(vector<vector<pair<int,int>>>& adj, int src) {

    int V = adj.size();

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(V, INT_MAX);

    dist[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (d > dist[u])
            continue;

        for (auto &p : adj[u]) {
            int v = p.first;
            int w = p.second;

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
        cout << "Introduceti doua argumente!\n";
        cout << "Sintaxa: p1.cpp {file_in} {file_out}\n";
        return 1;
    }

    int v, e, s;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> v >> e >> s;

    vector<vector<pair<int,int>>> adj(v);

    for (int i = 0; i < e; i++) {
        int x, y, w;
        fin >> x >> y >> w;
        adj[x].push_back(make_pair(y, w));
    }

    vector<int> result = dijkstra(adj, s);

    for (int d : result) {
        if (d == INT_MAX) {
            fout << "INF ";
        }
        else {
            fout << d <<  ' ';
        }
    }

    return 0;
}
