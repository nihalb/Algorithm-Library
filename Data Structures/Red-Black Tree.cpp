#include<stdio.h>

struct Node
{
    Node(int k, bool c);
    int key;
    Node* Left;
    Node* Right;
    bool color;
};

Node::Node(int k, bool c)
{
    key = k;
    Left = NULL;
    Right = NULL;
    color = c;
}

class RBTree
{
    public:
    RBTree();
    void insert(int k);
    Node* search(int k);
    void inOrderTraversal(Node* N);
    void inOrderTraversal();
    protected:
    bool isRed(Node* N);
    Node* leftRotate(Node* N);
    Node* rightRotate(Node* N);
    void flipColors(Node* N);
    Node* insert(Node* N, int k);
    Node* search(Node* N, int k);
    private:
    Node* root;
};

RBTree::RBTree()
{
    root = NULL;
}

bool RBTree::isRed(Node* N)
{
    if(N == NULL) return false;
    else return N->color;
}

Node* RBTree::leftRotate(Node* N)
{
    Node* temp = N->Right;
    temp->color = N->color;
    N->color = true;
    N->Right = temp->Left;
    temp->Left = N;
    return temp;
}

Node* RBTree::rightRotate(Node* N)
{
    Node* temp = N->Left;
    temp->color = N->color;
    N->color = true;
    N->Left = temp->Right;
    temp->Right = N;
    return temp;
}

void RBTree::flipColors(Node* N)
{
    N->Left->color = false;
    N->Right->color = false;
    N->color = true;
}

Node* RBTree::insert(Node* N, int k)
{
    if(N == NULL) return new Node(k,true);

    if(N->key > k) N->Left = insert(N->Left,k);
    else if(N->key < k) N->Right = insert(N->Right,k);

    if(isRed(N->Right) && !isRed(N->Left)) N = leftRotate(N);
    if(isRed(N->Left) && isRed(N->Left->Left)) N = rightRotate(N);
    if(isRed(N->Left) && isRed(N->Right)) flipColors(N);

    return N;
}

void RBTree::insert(int k)
{
    root = insert(root,k);
    root->color = false;
}

Node* RBTree::search(Node* N, int k)
{
    if(N->key == k) return N;
    else if(N->key > k) if(N->Left != NULL) return search(N->Left,k);
    else if(N->Right != NULL) return search(N->Right,k);
    return NULL;
}

Node* RBTree::search(int k)
{
    return search(root,k);
}

void RBTree::inOrderTraversal(Node* N)
{
    if(N != NULL)
    {
        inOrderTraversal(N->Left);
        printf("%d ",N->key);
        inOrderTraversal(N->Right);
    }
}

void RBTree::inOrderTraversal()
{
    inOrderTraversal(root);
}

int main()
{
    RBTree T;
    T.insert(2);
    T.insert(3);
    T.insert(11);
    T.insert(-1);
    T.insert(45);
    T.insert(-9);
    T.inOrderTraversal();
    return 0;
}
