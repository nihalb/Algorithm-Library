#include<stdio.h>

void sink(int A[], int i, int size)
{
    while(true)
    {
        int j = 2*i+1;
        if(j >= size) break;
        if(j+1 < size) if(A[j+1] > A[j]) j++;
        if(A[j] <= A[i]) break;
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        i = j;
    }
}

void buildHeap(int A[], int size)
{
    for(int i=size/2-1; i>=0; --i) sink(A,i,size);
}

void heapSort(int A[], int size)
{
    buildHeap(A,size);

    while(size >= 1)
    {
        size--;
        int temp = A[0];
        A[0] = A[size];
        A[size] = temp;
        sink(A,0,size);
    }
}

int main()
{
    int size;
    printf("Enter the number of elements\n");
    scanf("%d",&size);
    int* A = new int[size];
    printf("Enter the elements\n");
    for(int i=0; i<size; ++i) scanf("%d",&A[i]);
    heapSort(A,size);
    printf("The sorted elements are: \n");
    for(int i=0; i<size; ++i) printf("%d\n",A[i]);
    delete A;
    return 0;
}
