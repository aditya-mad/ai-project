#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void allIO(vector<vector<char>> &, int &, int &);
void checkAllWords(vector<vector<char>> &, vector<string> &, vector<string> &, int &, int &);
bool isWordPossible(vector<vector<char>> &, string &, vector<vector<bool>> &, int &, int &, int, int, int);
void printAns(vector<string> &);

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<char>> board(m, vector<char>(n));
    vector<string> words = {"START", "NOTE", "SAND", "STONED"};
    vector<string> ans;

    allIO(board, m, n);
    checkAllWords(board, words, ans, m, n);
    printAns(ans);

    return 0;
}

void allIO(vector<vector<char>> &board, int &m, int &n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }
}

void checkAllWords(vector<vector<char>> &board, vector<string> &words, vector<string> &ans, int &m, int &n)
{
    for (string word : words)
    {
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (word[0] == board[i][j] && isWordPossible(board, word, visited, m, n, i, j, 0))
                    ans.push_back(word);
            }
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