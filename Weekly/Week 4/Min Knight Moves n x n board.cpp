#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, start_i, start_j, end_i, end_j;

    cin >> n >> start_i >> start_j >> end_i >> end_j;

    vector<vector<bool>> visited(n, vector<bool>(n, true));
    vector<vector<int>> possible = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    queue<vector<int>> running;

    running.push({0, start_i, start_j});

    while (!running.empty())
    {
        vector<int> curr = running.front();
        running.pop();

        int moves = curr[0], ind_i = curr[1], ind_j = curr[2];

        if (ind_i == end_i && ind_j == end_j)
        {
            cout << moves;
            return 0;
        }

        visited[ind_i][ind_j] = false;

        for (int i = 0; i < 8; i++)
        {
            int next_i = ind_i + possible[i][0], next_j = ind_j + possible[i][1];
            if (next_i > -1 && next_i < n && next_j > -1 && next_j < n && visited[next_i][next_j])
            {
                running.push({moves + 1, next_i, next_j});
                visited[next_i][next_j] = false;
            }
        }
    }

    return 0;
}