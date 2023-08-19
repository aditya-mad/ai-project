#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef struct BinaryTree
{
    int data;
    struct BinaryTree *right;
    struct BinaryTree *left;
} TREE;

TREE *createNode();
void inorderTraversal(TREE *, vector<int> &);
void insertNode(TREE *, TREE *);
TREE *makeHeap(vector<int> &, int);
void levelOrderTraversal(TREE *);

int main()
{
    int size;
    cin >> size;

    TREE *root = nullptr;
    vector<int> heapdata;

    for (int i = 0; i < size; i++)
    {
        TREE *current_node = createNode();
        if (i == 0)
            root = current_node;
        else
            insertNode(root, current_node);
    }

    inorderTraversal(root, heapdata);

    TREE *HEAP = makeHeap(heapdata, 0);
    cout << "\n";
    levelOrderTraversal(HEAP);
    return 0;
}

TREE *createNode()
{
    TREE *create_block;
    create_block = (TREE *)malloc(sizeof(TREE));

    cin >> create_block->data;

    create_block->right = nullptr;
    create_block->left = nullptr;

    return create_block;
}

void insertNode(TREE *root, TREE *current_node)
{
    if (root->data > current_node->data)
    {
        if (root->left == nullptr)
            root->left = current_node;
        else
            insertNode(root->left, current_node);
    }
    else
    {
        if (root->right == nullptr)
            root->right = current_node;
        else
            insertNode(root->right, current_node);
    }
}

void inorderTraversal(TREE *root, vector<int> &heapdata)
{
    if (root != nullptr)
    {
        inorderTraversal(root->left, heapdata);
        heapdata.emplace_back(root->data);
        inorderTraversal(root->right, heapdata);
    }
}

TREE *makeHeap(vector<int> &heapdata, int index)
{
    if (index >= heapdata.size())
        return nullptr;

    TREE *root = (TREE *)malloc(sizeof(TREE));

    root->data = heapdata[index];

    root->left = makeHeap(heapdata, 2 * index + 1);
    root->right = makeHeap(heapdata, 2 * index + 2);

    return root;
}

void levelOrderTraversal(TREE *root)
{
    queue<TREE *> nodes;
    nodes.push(root);

    for (int curr = 0, level = 1; !nodes.empty(); curr++)
    {
        if (curr == level)
        {
            cout << endl;
            curr = 0;
            level *= 2;
        }

        cout << nodes.front()->data << " ";

        if (nodes.front()->left)
            nodes.push(nodes.front()->left);

        if (nodes.front()->right)
            nodes.push(nodes.front()->right);

        nodes.pop();
    }
}