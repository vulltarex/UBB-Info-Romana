#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src - 1] = 0;

    for (int i = 0; i < V; i++) {
        for (vector<int> edge : edges) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            int wt = edge[2];

            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                if (i == V - 1) {
                    return{-1};
                }
                dist[v] = dist[u] + wt;
            }
        }
    }
    return dist;
}

int main() {
    ifstream fin("graf.txt");
    int n, m, S;
    fin >> n >> m;
    vector<vector<int>> edges;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        edges.push_back({a, b, c});
    }
    fin >> S;
    vector<int> dist = bellmanFord(n, edges, S);
    if (dist.size() == 1 && dist[0] == -1) {
        cout << "Ciclu negativ.";
    }
    else {
        for (int d : dist) {
            if (d == INT_MAX) {
                cout << "INF ";
            }
            else {
                cout << d << ' ';
            }
        }
    }

    return 0;
}