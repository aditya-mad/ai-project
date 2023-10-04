#include <iostream>
#include <vector>
using namespace std;

void topological_sort(vector<vector<int>> &, int &);
int get_node(vector<vector<int>> &, int &);

int main()
{
    int nodes;

    cout << "enter no of nodes - ";
    cin >> nodes;

    vector<vector<int>> adjacency_matrix(nodes, vector<int>(nodes, 0));

    for (int i = 0; i < nodes; i++)
    {
        cout << "Enter node " << i + 1 << " edges - ";
        for (int j = 0; j < nodes; j++)
        {
            cin >> adjacency_matrix[i][j];
        }
    }

    cout << "Topological Sort is - ";
    topological_sort(adjacency_matrix, nodes);

    return 0;
}

void topological_sort(vector<vector<int>> &adjacency_matrix, int &nodes)
{
    int current_node = get_node(adjacency_matrix, nodes);

    if (current_node == -1)
        return;

    cout << current_node << " ";

    for (int i = 0; i < nodes; i++)
        adjacency_matrix[current_node][i] = 0;

    adjacency_matrix[current_node][current_node] = -1;

    topological_sort(adjacency_matrix, nodes);
}

int get_node(vector<vector<int>> &adjacency_matrix, int &nodes)
{
    int zero_node = -1;

    for (int i = 0; i < nodes; i++)
    {
        int count = 0;
        for (int j = 0; j < nodes; j++)
        {
            if (adjacency_matrix[j][i] == 0)
                count++;
            else
                break;
        }

        if (count == nodes)
        {
            zero_node = i;
            break;
        }
    }

    return zero_node;
}

/*
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 1 0 0
0 1 0 0 0 0
1 1 0 0 0 0
1 0 1 0 0 0
*/