/*4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de algoritmul BFS și distanța față de vârful sursă (arborele descoperit). */
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int INF = -1;

void bfs(int n, int graf[][101], int sursa)
{
    queue<int> q;
    vector<int> dist(n + 1, INF);
    q.push(sursa);
    dist[sursa] = 0;

    cout << "Nod: " << sursa << " Distanta: " << 0 << '\n';

    while (!q.empty())
    {
        int curent = q.front();
        q.pop();

        for (int i = 1; i <= n; i++)
        {
            if (graf[curent][i] == 1 and dist[i] == INF)
            {
                dist[i] = dist[curent] + 1;
                q.push(i);
                cout << "Nod: " << i << " Distanta: " << dist[i] << '\n';
            }
        }
    }
}

int main()
{
    int n, graf[101][101] = { 0 }, sursa, a, b;
    bool orientat = false;
    ifstream fin("graf.txt");
    fin >> n;
    cout << "0. Neorientat\n1. Orientat\nAlegeti tipul de graf: ";
    cin >> orientat;
    while (fin >> a >> b)
    {
        graf[a][b] = 1;
        if (!orientat)
        {
            graf[b][a] = 1;
        }
    }
    cout << "Introduceti varful sursa: ";
    cin >> sursa;
    bfs(n, graf, sursa);
}