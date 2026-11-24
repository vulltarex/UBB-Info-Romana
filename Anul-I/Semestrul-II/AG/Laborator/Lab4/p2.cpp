#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int m;
    fin >> m;
    vector<int> prufer(m);
    int n = m + 1;
    vector<int> degree(n, 1);
    for (int i = 0; i < m; ++i) {
        fin >> prufer[i];
        degree[prufer[i]]++;
    }
    set<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            leaves.insert(i);
        }
    }
    vector<int> parent(n, -1);
    for (int i = 0; i < m; ++i) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
        int p = prufer[i];
        parent[leaf] = p;
        degree[p]--;
        if (degree[p] == 1) {
            leaves.insert(p);
        }
    }
    fout << n << "\n";
    for (int i = 0; i < n; ++i) {
        fout << parent[i] << (i == n - 1 ? "" : " ");
    }
    fout << "\n";
    return 0;
}
