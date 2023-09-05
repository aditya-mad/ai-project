// min steps for knight to reach destination from source/.
#include <iostream>
#include <vector>
using namespace std;

void isPathPossible(vector<vector<bool>> &, int, int, int);
int start_i, start_j, end_i, end_j;
int ans = 7;

int main()
{
    cin >> start_i >> start_j >> end_i >> end_j;

    vector<vector<bool>> visited(8, vector<bool>(8, false));

    isPathPossible(visited, start_i, start_j, 0);

    cout << ans << endl;
    return 0;
}

void isPathPossible(vector<vector<bool>> &visited, int i, int j, int step)
{
    if (i < 0 || j < 0 || j >= 8 || i >= 8 || visited[i][j] || step > 6)
        return;

    if (i == end_i && j == end_j)
    {
        ans = min(ans, step);
        return;
    }

    visited[i][j] == true;

    isPathPossible(visited, i - 2, j - 1, step + 1);
    isPathPossible(visited, i - 2, j + 1, step + 1);
    isPathPossible(visited, i - 1, j - 2, step + 1);
    isPathPossible(visited, i - 1, j + 2, step + 1);
    isPathPossible(visited, i + 2, j + 1, step + 1);
    isPathPossible(visited, i + 2, j - 1, step + 1);
    isPathPossible(visited, i + 1, j + 2, step + 1);
    isPathPossible(visited, i + 1, j - 2, step + 1);

    visited[i][j] = false;

    return;
}