#include<stdio.h>

// Index of BIT is from 1 to size : [1,size]

struct BIT
{
    BIT();
    BIT(int n);
    ~BIT();
    int read(int idx);
    void update(int idx, int value);
    int size;
    int* tree;
};

BIT::BIT()
{
    size = 0;
}

BIT::BIT(int n)
{
    size = n+1;
    tree = new int[size];
    for(int i=1; i<=size ; ++i)
    {
        tree[i] = 0;
    }
}

BIT::~BIT()
{
    delete[] tree;
}

int BIT::read(int idx)
{
    int sum = 0;
    while(idx > 0)
    {
        sum += tree[idx];
        idx -= idx&(-idx);
    }
    return sum;
}

void BIT::update(int idx, int value)
{
	while(idx <= n)
	{
		tree[idx] += value;
		idx += idx&(-idx);
	}
}

int main()
{
    
    return 0;
}
