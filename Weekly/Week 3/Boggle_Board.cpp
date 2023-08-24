#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void allIO(vector<vector<char>> &, unordered_map<char, vector<pair<int, int>>> &, int &, int &);
void checkAllWords(vector<vector<char>> &, unordered_map<char, vector<pair<int, int>>> &, vector<string> &, vector<string> &, int &, int &);
bool isWordPossible(vector<vector<char>> &, string &, vector<vector<bool>> &, int &, int &, int, int, int);
void printAns(vector<string> &);

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<char>> board(m, vector<char>(n));
    unordered_map<char, vector<pair<int, int>>> keys;
    vector<string> words = {"START", "NOTE", "SAND", "STONED"};
    vector<string> ans;

    allIO(board, keys, m, n);
    checkAllWords(board, keys, words, ans, m, n);
    printAns(ans);

    return 0;
}

void allIO(vector<vector<char>> &board, unordered_map<char, vector<pair<int, int>>> &keys, int &m, int &n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
            keys[board[i][j]].push_back(make_pair(i, j));
        }
    }
}

void checkAllWords(vector<vector<char>> &board, unordered_map<char, vector<pair<int, int>>> &keys, vector<string> &words, vector<string> &ans, int &m, int &n)
{
    for (auto x : words)
    {
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (auto y : keys[x[0]])
        {
            if (isWordPossible(board, x, visited, m, n, y.first, y.second, 0))
                ans.push_back(x);
        }
    }
}

bool isWordPossible(vector<vector<char>> &board, string &search, vector<vector<bool>> &visited, int &m, int &n, int i, int j, int ind)
{
    if (ind == search.size())
        return true;

    if (i < 0 || j < 0 || i >= m || j >= n || search[ind] != board[i][j] || visited[i][j])
        return false;

    visited[i][j] = true;

    bool check_next = false;

    check_next |= isWordPossible(board, search, visited, m, n, i, j - 1, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i, j + 1, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i - 1, j, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i + 1, j, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i - 1, j - 1, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i + 1, j - 1, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i - 1, j + 1, ind + 1);
    check_next |= isWordPossible(board, search, visited, m, n, i + 1, j + 1, ind + 1);

    visited[i][j] = false;

    return check_next;
}

void printAns(vector<string> &ans)
{
    cout << endl;
    for (string word : ans)
    {
        cout << word << " ";
    }
}