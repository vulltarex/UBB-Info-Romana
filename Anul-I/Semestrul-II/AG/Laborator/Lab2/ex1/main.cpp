#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
/*
1. Implementați algoritmul lui Moore pentru un graf orientat neponderat (algoritm bazat pe Breath-first search, vezi cursul 2).
Datele sunt citete din fisierul graf.txt. Primul rând din graf.txt conține numărul vârfurilor, iar următoarele rânduri conțin muchiile grafului.
Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf (vârful sursa poate fi citit de la tastatura).
 */
using namespace std;

const int INF = -1;

void moore(int n, int graf[][101], int sursa, int dest)
{
    queue<int> q;
    vector<int> dist(n + 1, INF);
    vector<int> parinte(n + 1, 0);

    dist[sursa] = 0;
    q.push(sursa);

    while (!q.empty())
    {
        int curent = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (graf[curent][i] == 1 && dist[i] == INF)
            {
                parinte[i] = curent;
                dist[i] = dist[curent] + 1;
                q.push(i);
            }
        }
    }

    if (dist[dest] == INF)
    {
        cout << "Nu exista drum!";
        return;
    }

    int k = dist[dest];
    vector<int> traseu(k + 1);
    traseu[k] = dest;
    while (k)
    {
        traseu[k - 1] = parinte[traseu[k]];
        k--;
    }

    cout << "Distanta: " << dist[dest] << '\n';
    cout << "Traseul: ";
    for (int i = 0; i < traseu.size(); i++)
    {
        cout << traseu[i] << ' ';
    }
}

int main()
{
    int n, a, b, graf[101][101] = { 0 };
    ifstream fin("graf.txt");
    fin >> n;
    while (fin >> a >> b)
    {
        graf[a][b] = 1;
    }
    int sursa, dest;
    cout << "Introduceti varful sursa: ";
    cin >> sursa;
    cout << "Introduceti varful destinatie: ";
    cin >> dest;
    moore(n, graf, sursa, dest);

    return 0;
}