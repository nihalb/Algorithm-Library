#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int partition(int A[], int start, int end)
{
    int i = start;
    int j = end+1;
    int temp;

    while(true)
    {
        while(A[++i] < A[start]) if(i == end) break;
        while(A[--j] > A[start]) {}
        if(j<=i) break;

        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    temp = A[start];
    A[start] = A[j];
    A[j] = temp;

    return j;
}

void quickSort(int A[], int start, int end)
{
    if(start >= end) return;
    int split = partition(A,start,end);
    quickSort(A,start,split-1);
    quickSort(A,split+1,end);
}

void qSort(int A[], int size)
{
    quickSort(A,0,size-1);
}

int qSelect(int A[], int k, int size)
{
    int start = 0;
    int end = size-1;

    k--;

    while(start < end)
    {
        int split = partition(A,start,end);
        if(k > split) start = split + 1;
        else if(k < split) end = split -1;
        else break;
    }

    return A[k];
}

int main()
{

}
