#include<stdio.h>

const int max_n = 200000 + 5;
int segment[max_n];
int count;

void get_size(int n)
{
    count = 1;
    while(n)
    {
       n >>= 1;
       count++;
    }
    count = 1<<count;
}

void init(int index, int A[], int a, int b)
{
    if(a > b) return;
    if(a == b)
    {
        segment[index] = A[a];
        return;
    }
    int mid = a + (b-a)/2;
    init(2*index,A,a,mid);
    init(2*index+1,A,mid+1,b);
    segment[index] = segment[2*index] + segment[2*index+1];
}

void initialize(int A[], int n)
{
    get_size(n);
    init(1, A, 0, n-1);
}

void update(int index, int a, int b, int x, int v)
{
    if(a > b || x < a || x > b) return;
    if(a == b)
    {
        segment[index] = v;
        return;
    }
    int mid = a + (b-a)/2;
    update(2*index,a,mid,x,v);
    update(2*index+1,mid+1,b,x,v);
    segment[index] = segment[2*index] + segment[2*index+1];
}

int query(int index, int left, int right, int a, int b)
{
    if(left > right || right < a || left > b) return 0;
    if(a <= left && b >= right) return segment[index];
    int mid = left + (right-left)/2;
    return query(2*index,left,mid,a,b) + query(2*index+1,mid+1,right,a,b);
}

int main()
{
    int A[9] = {1,6,2,4,5,7,3,12,45};
    return 0;
}
