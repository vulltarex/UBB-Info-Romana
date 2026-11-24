#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//3. Să se scrie un program care găsește o soluție pentru unul din următoarele labirinturi: labirint_1.txt, labirint_2.txt, labirint_cuvinte.txt.
//Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S și punctul de oprire este indicat de litera F, spre deosebire de labirintul 1 și 2, labirintul 3 nu are o soluție unică.

//program scris pt. labirint 1 si 2

using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool dfs_labirint(vector<string> &maze, int x, int y)
{
    if (x < 0 || x >= maze.size() || y < 0 || y >= maze[x].size() || maze[x][y] == '*' || maze[x][y] == '-' || maze[x][y] == '1')
    {
        return false;
    }

    if (maze[x][y] == 'F')
    {
        return true;
    }

    bool is_start = maze[x][y] == 'S';

    if (!is_start)
    {
        maze[x][y] = '*';
    }

    for (int i = 0; i < 4; i++)
    {
        if (dfs_labirint(maze, x + dx[i], y + dy[i]))
        {
            return true;
        }
    }

    if (!is_start)
    {
        maze[x][y] = '-';
    }

    return false;

}

int main()
{
    string labirint;
    int cmd;
    cout << "1. Labirint 1\n2. Labirint 2\nAlegeti labirintul: ";
    cin >> cmd;
    if (cmd == 1)
    {
        labirint = "labirint_1.txt";
    }
    else
    {
        labirint = "labirint_2.txt";
    }
    ifstream fin(labirint);
    if (!fin)
    {
        return 1;
    }

    vector<string> maze;
    string line;
    while (getline(fin, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        if (!line.empty())
        {
            maze.push_back(line);
        }
    }
    int start_x = -1, start_y = -1;
    bool gasit = false;
    for (size_t i = 0; i < maze.size() && !gasit; i++)
    {
        for (size_t j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j] == 'S')
            {
                start_x = i;
                start_y = j;
                gasit = true;
                break;
            }
        }
    }

    if (dfs_labirint(maze, start_x, start_y))
    {
        for (size_t i = 0; i < maze.size(); i++)
        {
            cout << maze[i] << '\n';
        }
    }
    else
    {
        cout << "Nu exista solutie.";
    }

    return 0;
}