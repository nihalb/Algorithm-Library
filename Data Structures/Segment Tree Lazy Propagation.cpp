#include<stdio.h>

class SegmentTree
{
    public:
    SegmentTree();
    SegmentTree(int size);
    SegmentTree(int A[], int size);
    ~SegmentTree();
    void LazyInitialize(int index, int A[], int a, int b);
    void LazyUpdate(int index, int a, int b, int x, int y, int v);
    int LazyQuery(int index, int left, int right, int a, int b);
    private:
    int* segment;
    int* lazy;
    int count;
};

SegmentTree::SegmentTree()
{
    count = 0;
}

SegmentTree::SegmentTree(int size)
{
    count = 1;
    while(size)
    {
        size >>= 1;
        count++;
    }
    count = 1<<count;
    segment = new int[count];
    lazy = new int[count];
}

SegmentTree::SegmentTree(int A[], int size)
{
    count = 1;
    int temp = size;
    while(temp)
    {
        temp >>= 1;
        count++;
    }
    count = 1<<count;
    segment = new int[count];
    lazy = new int[count];
    LazyInitialize(1,A,0,size-1);
}

SegmentTree::~SegmentTree()
{
    delete[] segment;
    delete[] lazy;
}

void SegmentTree::LazyInitialize(int index, int A[], int a, int b)
{
    if(a > b) return;
    lazy[index] = 0;
    if(a == b)
    {
        segment[index] = A[a];
        return;
    }
    int mid = a + (b-a)/2;
    LazyInitialize(2*index,A,a,mid);
    LazyInitialize(2*index+1,A,mid+1,b);
    segment[index] = segment[2*index] + segment[2*index+1];
}

void SegmentTree::LazyUpdate(int index, int a, int b, int x, int y, int v)
{
    if(lazy[index] != 0)
    {
        segment[index] += (b-a+1)*lazy[index];
        if(a < b)
        {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
    if(a > b || x > b || y < a) return;
    if(x <= a && y >= b)
    {
        segment[index] += v*(b-a+1);
        if(a < b)
        {
            lazy[2*index] += v;
            lazy[2*index+1] += v;
        }
        return;
    }
    int mid = a + (b-a)/2;
    LazyUpdate(2*index,a,mid,x,y,v);
    LazyUpdate(2*index+1,mid+1,b,x,y,v);
    segment[index] = segment[2*index] + segment[2*index+1];
}

int SegmentTree::LazyQuery(int index, int left, int right, int a, int b)
{
    if(left > right || a > right || b < left) return 0;
    if(lazy[index] != 0)
    {
        segment[index] += (right-left+1)*lazy[index];
        if(left < right)
        {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
    if(a <= left && b >= right) return segment[index];
    int mid = left + (right-left)/2;
    return LazyQuery(2*index,left,mid,a,b) + LazyQuery(2*index+1,mid+1,right,a,b);
}

int main()
{
    int A[6] = {2,8,3,5,6,0};
    SegmentTree T(A,6);
    T.LazyUpdate(1,0,5,2,4,-1);
    printf("%d\n",T.LazyQuery(1,0,5,0,3));
	return 0;
}
