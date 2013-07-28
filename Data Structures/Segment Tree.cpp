#include<stdio.h>

class SegmentTree
{
    public:
    SegmentTree();
    SegmentTree(int size);
    SegmentTree(int A[], int size);
    ~SegmentTree();
    void Initialize(int index, int A[], int a, int b);
    void Update(int index, int a, int b, int x, int v);
    int Query(int index, int left, int right, int a, int b);
    private:
    int* segment;
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
    Initialize(1,A,0,size-1);
}

SegmentTree::~SegmentTree()
{
    delete[] segment;
}

void SegmentTree::Initialize(int index, int A[], int a, int b)
{
    if(a > b) return;
    if(a == b)
    {
        segment[index] = A[a];
        return;
    }
    int mid = a + (b-a)/2;
    Initialize(2*index,A,a,mid);
    Initialize(2*index+1,A,mid+1,b);
    segment[index] = segment[2*index] + segment[2*index+1];
}

void SegmentTree::Update(int index, int a, int b, int x, int v)
{
    if(a > b || x < a || x > b) return;
    if(a == b)
    {
        segment[index] = v;
        return;
    }
    int mid = a + (b-a)/2;
    Update(2*index,a,mid,x,v);
    Update(2*index+1,mid+1,b,x,v);
    segment[index] = segment[2*index] + segment[2*index+1];
}

int SegmentTree::Query(int index, int left, int right, int a, int b)
{
    if(left > right || right < a || left > b) return 0;
    if(a <= left && b >= right) return segment[index];
    int mid = left + (right-left)/2;
    return Query(2*index,left,mid,a,b) + Query(2*index+1,mid+1,right,a,b);
}

int main()
{
	int A[9] = {1,6,2,4,5,7,3,12,45};
	SegmentTree T(100000);
	return 0;
}
