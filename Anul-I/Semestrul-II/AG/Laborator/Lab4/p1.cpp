#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int n;
    fin >> n;
    vector<int> parent(n);
    vector<int> degree(n, 0);
    for (int i = 0; i < n; ++i) {
        fin >> parent[i];
        if (parent[i] != -1) {
            degree[parent[i]]++;
        }
    }
    set<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 0 && parent[i] != -1) {
            leaves.insert(i);
        }
    }
    vector<int> prufer;
    for (int i = 0; i < n - 1; ++i) {
        if (leaves.empty()) break;
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
        int p = parent[leaf];
        prufer.push_back(p);
        degree[p]--;
        if (degree[p] == 0 && parent[p] != -1) {
            leaves.insert(p);
        }
    }
    fout << prufer.size() << "\n";
    for (size_t i = 0; i < prufer.size(); ++i) {
        fout << prufer[i] << (i + 1 == prufer.size() ? "" : " ");
    }
    fout << "\n";
    return 0;
}
