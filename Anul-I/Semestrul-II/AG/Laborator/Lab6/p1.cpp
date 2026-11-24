#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n, m;
    if (!(fin >> n >> m)) return 0;

    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 0);
    sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return deg[a] > deg[b];
    });

    vector<int> color(n, -1);
    int max_color = -1;

    for (int u : nodes) {
        vector<bool> used(n, false);
        for (int v : adj[u]) {
            if (color[v] != -1) {
                used[color[v]] = true;
            }
        }
        int c = 0;
        while (used[c]) c++;
        color[u] = c;
        max_color = max(max_color, c);
    }

    fout << max_color + 1 << "\n";
    for (int i = 0; i < n; ++i) {
        fout << color[i] << (i == n - 1 ? "" : " ");
    }
    fout << "\n";

    return 0;
}
