#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    if (!(fin >> V >> E)) return 0;

    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<bool> used(E, false);
    vector<int> path;
    vector<int> curr_edge(V, 0);
    vector<int> st;

    st.push_back(0);

    while (!st.empty()) {
        int u = st.back();
        bool found = false;
        
        while (curr_edge[u] < adj[u].size()) {
            auto edge = adj[u][curr_edge[u]++];
            if (!used[edge.second]) {
                used[edge.second] = true;
                st.push_back(edge.first);
                found = true;
                break;
            }
        }
        
        if (!found) {
            path.push_back(u);
            st.pop_back();
        }
    }

    for (size_t i = 0; i < path.size(); ++i) {
        fout << path[i] << (i + 1 == path.size() ? "" : " ");
    }
    fout << "\n";

    return 0;
}
