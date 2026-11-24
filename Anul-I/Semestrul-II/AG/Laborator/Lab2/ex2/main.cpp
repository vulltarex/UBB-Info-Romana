#include <iostream>
#include <fstream>
/*
 2. Sa se determine închiderea transitivă a unui graf orientat. (Închiderea tranzitivă poate fi reprezentată ca matricea care descrie,
 pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf. Matricea inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.)
 ex. figura inchidere_tranzitiva.png - pentru graful de sus se construieste matricea de jos care arata inchiderea tranzitiva.*/
using namespace std;

bool vizitat[101];

void dfs(int n, int graf[][101], int nod)
{
    vizitat[nod] = true;
    for (int i = 1; i <= n; i++)
    {
        if (graf[nod][i] == 1 && vizitat[i] == false)
        {
            dfs(n, graf, i);
        }
    }
}

int main()
{
    int n, graf[101][101] = { 0 }, a, b, inc_tranz[101][101] = { 0 };
    ifstream fin("graf.txt");
    fin >> n;
    // while (fin >> a >> b)
    // {
    //     graf[a][b] = 1;
    // }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fin >> graf[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vizitat[j] = false;
        }
        dfs(n, graf, i);
        for (int j = 1; j <= n; j++)
        {
            if (vizitat[j])
            {
                inc_tranz[i][j] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << inc_tranz[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}