//5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de apelul recursiv al procedurii DFS_VISIT(G, u) (apadurea descoperită de DFS).
#include <iostream>
#include <fstream>

using namespace std;

bool vizitat[101] = { false };

void dfs_visit(int n, int graf[][101], int nod)
{
    vizitat[nod] = true;
    cout << nod << ' ';
    for (int i = 1; i <= n; i++)
    {
        if (graf[nod][i] == 1 && vizitat[i] == false)
        {
            dfs_visit(n, graf, i);
        }
    }
}

int main()
{
    ifstream fin("graf.txt");
    int n, graf[101][101] = { 0 }, a, b;
    bool orientat;
    fin >> n;
    cout << "0. Neorientat\n1. Orientat\nAlegeti tipul grafului: ";
    cin >> orientat;
    while (fin >> a >> b)
    {
        graf[a][b] = 1;
        if (!orientat)
        {
            graf[b][a] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (vizitat[i] == false)
        {
            cout << "\n------\n";
            dfs_visit(n, graf, i);
        }
    }
    return 0;
}