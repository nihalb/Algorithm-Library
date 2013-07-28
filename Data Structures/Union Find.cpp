#include<stdio.h>

class UnionFind
{
    public:
    UnionFind(int n);
    ~UnionFind();
    void Union(int p, int q);
    bool Connected(int p, int q);
    protected:
    int Root(int p);
    private:
    int* Parent;
    int* Weight;
    int n;
};

UnionFind::UnionFind(int n)
{
    this->n = n;
    Parent = new int[n];
    Weight = new int[n];
    for(int i=0; i<n; ++i)
    {
        Parent[i] = i;
        Weight[i] = 1;
    }
}

UnionFind::~UnionFind()
{
    delete[] Parent;
    delete[] Weight;
}

void UnionFind::Union(int p, int q)
{
    int pRoot = Root(p);
    int qRoot = Root(q);
    if(pRoot != qRoot)
    {
        if(Weight[pRoot] < Weight[qRoot])
        {
            Parent[pRoot] = qRoot;
            Weight[qRoot] += Weight[pRoot];
        }
        else
        {
            Parent[qRoot] = pRoot;
            Weight[pRoot] += Weight[qRoot];
        }
    }
}

bool UnionFind::Connected(int p, int q)
{
    return (Root(p)==Root(q));
}

int UnionFind::Root(int p)
{
    int r = Parent[p];
    while(r != Parent[r]) r = Parent[r];
    int i = p;
    int temp;
    while(i != r)
    {
        temp = Parent[i];
        Parent[i] = r;
        i = temp;
    }
    return r;
}

int main()
{
    return 0;
}
