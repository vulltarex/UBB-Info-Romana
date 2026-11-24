#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

bool bfs(int V, const vector<vector<int>>& adj, const vector<vector<int>>& capacity, int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int curr = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[curr]) {
            if (parent[next] == -1 && capacity[curr][next] > 0) {
                parent[next] = curr;
                int new_flow = min(flow, capacity[curr][next]);

                if (next == t) {
                    return true;
                }
                q.push({next, new_flow});
            }
        }
    }
    return false;
}

int max_flow(int V, vector<vector<int>>& adj, vector<vector<int>>& capacity, int s, int t) {
    int flow = 0;
    vector<int> parent(V);

    while (bfs(V, adj, capacity, s, t, parent)) {
        int path_flow = INT_MAX;
        int curr = t;

        while (curr != s) {
            int prev = parent[curr];
            path_flow = min(path_flow, capacity[prev][curr]);
            curr = prev;
        }

        flow += path_flow;
        curr = t;

        while (curr != s) {
            int prev = parent[curr];
            capacity[prev][curr] -= path_flow;
            capacity[curr][prev] += path_flow;
            curr = prev;
        }
    }
    return flow;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Utilizare: " << argv[0] << " <fisier_intrare> <fisier_iesire>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin.is_open()) {
        cerr << "Eroare la deschiderea fisierului de intrare\n";
        return 1;
    }

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<int>> adj(V);
    vector<vector<int>> capacity(V, vector<int>(V, 0));

    for (int i = 0; i < E; ++i) {
        int u, v, c;
        fin >> u >> v >> c;

        if (capacity[u][v] == 0 && capacity[v][u] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        capacity[u][v] += c;
    }

    int s = 0;
    int t = V - 1;

    fout << max_flow(V, adj, capacity, s, t) << "\n";

    fin.close();
    fout.close();

    return 0;
}