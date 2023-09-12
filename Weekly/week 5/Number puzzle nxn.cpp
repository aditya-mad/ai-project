#include <bits/stdc++.h>
using namespace std;

void inputBoard(vector<vector<int>> &, int &);
void solveBoard(vector<vector<int>> &, int);
int countMisplace(vector<vector<int>>, vector<vector<int>>, int, int, int, int, int);
bool isDone(vector<vector<int>>, int);
void getSpacePos(vector<vector<int>> &, int, int &, int &);
void makeAns(vector<vector<int>> &, int);

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    inputBoard(board, n);
    solveBoard(board, n);
}

void inputBoard(vector<vector<int>> &nums, int &n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> nums[i][j];
        }
    }
}

void solveBoard(vector<vector<int>> &board, int n)
{
    vector<int> possible(4);
    int move = 0;
    vector<vector<int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    vector<vector<int>> ans(n, vector<int>(n));

    for (int i = 0, num = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++, num++)
        {
            ans[i][j] = num;
        }
    }

    ans[n - 1][n - 1] = 0;

    while (ans != board)
    {
        int is, js;

        getSpacePos(board, n, is, js);

        move++;
        possible[0] = move + countMisplace(board, ans, n, is + 1, js, is, js);
        possible[1] = move + countMisplace(board, ans, n, is - 1, js, is, js);
        possible[2] = move + countMisplace(board, ans, n, is, js + 1, is, js);
        possible[3] = move + countMisplace(board, ans, n, is, js - 1, is, js);

        int best = 0;
        for (int i = 0; i < 4; i++)
        {
            if (possible[best] > possible[i])
                best = i;
        }

        board[is][js] = board[is + moves[best][0]][js + moves[best][1]];
        board[is + moves[best][0]][js + moves[best][1]] = 0;
        cout << move << "\n";
    }

    cout << move;
}

int countMisplace(vector<vector<int>> nums, vector<vector<int>> ans, int n, int k, int l, int is, int js)
{
    if (k < 0 || k >= n || l < 0 || l >= n)
        return 1e5;

    nums[is][js] = nums[k][l];
    nums[k][l] = 0;

    int misplace = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool cont = true;
            for (int k = 0; k < n && cont; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    if (ans[i][j] == nums[k][l])
                    {
                        misplace += (abs(i - k) + abs(j - l));
                        cont = false;
                        break;
                    }
                }
            }
        }
    }
    return misplace;
}

bool isDone(vector<vector<int>> board, int n)
{
    board[n - 1][n - 1] = n * n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != (i * n) + j + 1)
                return false;
        }
    }
    return true;
}

void getSpacePos(vector<vector<int>> &nums, int n, int &is, int &js)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (nums[i][j] == 0)
            {
                is = i;
                js = j;
                return;
            }
}
