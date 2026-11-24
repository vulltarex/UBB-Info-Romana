#include <fstream>
#include <iostream>
#include <vector>
#include <climits>

int minKey(const std::vector<int>& key, const std::vector<bool>& mstSet) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < key.size(); v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Introduceti exact doua argumente!";
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    int V, E;
    fin >> V >> E;

    std::vector<std::vector<std::pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int x, y, w;
        fin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }

    std::vector<int> parent(V, -1);
    std::vector<int> key(V, INT_MAX);
    std::vector<bool> mstSet(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!mstSet[v] && w < key[v]) {
                parent[v] = u;
                key[v] = w;
            }
        }
    }

    int costTotal = 0;
    int numarMuchii = 0;

    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            costTotal += key[i];
            numarMuchii++;
        }
    }

    fout << costTotal << "\n";
    fout << numarMuchii << "\n";
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            fout << parent[i] << " " << i << "\n";
        }
    }

    return 0;
}