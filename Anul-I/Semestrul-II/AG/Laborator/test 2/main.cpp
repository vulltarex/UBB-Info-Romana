/*
Caz real de utilizare:
 Decodarea Prüfer reconstruiește o topologie arborescentă (ex. o rețea de calculatoare ierarhică)
 plecând de la o secvență compactă (codul Prüfer), fiind utilă în stocarea ultra-compactă
 a structurilor de date.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    int n;
    if (!(fin >> n)) return 0;

    int m = n - 2;
    vector<int> seq(m);
    vector<int> degree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        fin >> seq[i];
        degree[seq[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> parent(n + 1, -1);
    for (int i = 0; i < m; ++i) {
        int u = pq.top();
        pq.pop();

        int p = seq[i];
        parent[u] = p;

        degree[p]--;
        if (degree[p] == 0) {
            pq.push(p);
        }
    }

    int u = pq.top();
    pq.pop();
    parent[u] = pq.top();
    pq.pop();

    for (int i = 1; i <= n; ++i) {
        fout << parent[i] << ' ';
    }
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
