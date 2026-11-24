#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int g[101][101] = { 0 }, n, vizitat[101] = { 0 }, mat_dist[101][101];

int grad(int varf)
{
    /*
     Determina gradul unui varf insumand linia corespunzatoare din matricea de adiacenta
     sum - suma elementelor liniei, egal cu gradul varfului
     */
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += g[varf][i];
    }
    return sum;
}

void afis_varfuri_izolate()
{
    /*
     Determina si afiseaza varfurile izolate
     */
    cout << "Varfurile izolate sunt: ";
    bool exista_izolate = false;

    for (int i = 1; i <= n; i++)
    {
        if (grad(i) == 0)
        {
            exista_izolate = true;
            cout << i << ' ';
        }
    }
    if (exista_izolate == false)
    {
        cout << '-';
    }
    cout << '\n';
}

bool is_regular()
{
    /*
     Determina daca un graf este regular si returneaza true sau false in functie de indeplinirea conditiei
     */
    int grad_anterior = grad(1);

    for (int i = 2; i <= n; i++)
    {
        if (grad(i) != grad_anterior)
        {
            return false;
        }
        grad_anterior = grad(i);
    }

    return true;
}

void dfs(int varf)
{
    /*
     Parcurge graful in adancime, setand valorile din vectorul "vizitat" la 1 daca varful
     */
    vizitat[varf] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (g[varf][i] == 1 and vizitat[i] == 0)
        {
            dfs(i);
        }
    }
}

bool conex()
{
    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        if (vizitat[i] == 0)
        {
            return false;
        }
    }
    return true;
}

void calcul_distanta(int start)
{
    for (int i = 1; i <= n; i++)
    {
        mat_dist[start][i] = -1;
    }

    queue<int> q;
    q.push(start);
    mat_dist[start][start] = 0;

    while (!q.empty())
    {
        int curent = q.front();
        q.pop();

        for (int i = 1; i <= n; i++)
        {
            if (g[curent][i] == 1 and mat_dist[start][i] == -1)
            {
                mat_dist[start][i] = mat_dist[start][curent] + 1;
                q.push(i);
            }
        }
    }
}

int main()
{
    int a, b;
    ifstream fin("in.txt");

    fin >> n;
    while (fin >> a >> b)
    {
        g[a][b] = g[b][a] = 1;
    }

    afis_varfuri_izolate();

    if (is_regular())
    {
        cout << "Graful este regular\n";
    }
    else
    {
        cout << "Graful nu este regular\n";
    }

    if (conex())
    {
        cout << "Graful este conex\n";
    }
    else
    {
        cout << "Graful nu este conex\n";
    }

    for (int i = 1; i <= n; i++)
    {
        calcul_distanta(i);
    }
    cout << "Matricea de distante:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << mat_dist[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}