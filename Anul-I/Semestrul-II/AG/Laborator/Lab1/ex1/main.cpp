#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("in.txt");
    int n, a, b, mat_ad1[100][100], mat_inc[100][1000], mat_ad2[100][100];
    vector<int> list_ad1[100];
    fin >> n;
    //initializare matrici de adiacenta si incidenta cu 0
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            mat_ad1[i][j] = mat_ad2[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < 1000; j++)
        {
            mat_inc[i][j] = 0;
        }
    }
    //input -> matrice adiacenta
    while (fin >> a >> b)
    {
        mat_ad1[a][b] = mat_ad1[b][a] = 1;
    }
    cout << "Matrice de adiacenta:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << mat_ad1[i][j] << ' ';
        }
        cout << '\n';
    }
    //matrice adiacenta -> lista adiacenta
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (mat_ad1[i][j] != 0)
            {
                list_ad1[i].push_back(j);
            }
        }
    }
    cout << "Lista de adiacenta:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < list_ad1[i].size(); j++)
        {
            cout << list_ad1[i][j] << ' ';
        }
        cout << '\n';
    }
    //lista adiacenta -> matrice incidenta
    int muchie = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < list_ad1[i].size(); j++)
        {
            if (i < list_ad1[i][j])
            {
                mat_inc[i][muchie] = mat_inc[list_ad1[i][j]][muchie] = 1;
                muchie++;
            }
        }
    }
    cout << "Matricea de incidenta:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < muchie; j++)
        {
            cout << mat_inc[i][j] << ' ';
        }
        cout << '\n';
    }
    //matrice de incidenta -> lista de adiacenta
    vector<int> list_ad2[100];
    for (int j = 1; j < muchie; j++)
    {
        vector<int> noduri;
        for (int i = 1; i <= n; i++)
        {
            if (mat_inc[i][j])
            {
                noduri.push_back(i);
            }
        }
        list_ad2[noduri[0]].push_back(noduri[1]);
        list_ad2[noduri[1]].push_back(noduri[0]);
        noduri.clear();
    }
    cout << "A doua lista de adiacenta:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < list_ad2[i].size(); j++)
        {
            cout << list_ad2[i][j] << ' ';
        }
        cout << '\n';
    }
    //lista de adiacenta -> matrice de adiacenta
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < list_ad2[i].size(); j++)
        {
            mat_ad2[i][list_ad2[i][j]] = mat_ad2[list_ad2[i][j]][i] = 1;
        }
    }
    cout << "A doua matrice de adiacenta:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << mat_ad2[i][j] << ' ';
        }
        cout << '\n';
    }

    fin.close();
    return 0;
}
