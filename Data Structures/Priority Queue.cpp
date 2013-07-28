#include<stdio.h>

#define PQSize 10000

class MaxPQ
{
    public:
    MaxPQ();
    bool isEmpty();
    void insert(int k);
    int deleteMax();
    int returnMax();
    protected:
    void swim(int i);
    void sink(int i);
    private:
    int* elements;
    int size;
    int last;
};

MaxPQ::MaxPQ()
{
    size = PQSize;
    last = 1;
    elements = new int[size];
}

bool MaxPQ::isEmpty()
{
    if(last == 1) return true;
    return false;
}

void MaxPQ::swim(int i)
{
    while(i>1)
    {
        if(elements[i/2] >= elements[i]) break;
        int temp = elements[i/2];
        elements[i/2] = elements[i];
        elements[i] = temp;
        i /= 2;
    }
}

void MaxPQ::sink(int i)
{
    while(true)
    {
        int j = 2*i;
        if(j >= last) break;
        if(j+1 < last) if(elements[j+1] > elements[j]) j++;
        if(elements[j] <= elements[i]) break;
        int temp = elements[i];
        elements[i] = elements[j];
        elements[j] = temp;
        i = j;
    }
}

void MaxPQ::insert(int k)
{
    try
    {
        if(last < size)
        {
            elements[last] = k;
            swim(last);
            last++;
        }
        throw 1;
    }
    catch(int e)
    {
        printf("Exception %d: Max Priority Queue is full\n",e);
    }
}

int MaxPQ::deleteMax()
{
    try
    {
        if(!isEmpty())
        {
            int temp = elements[1];
            elements[1] = elements[--last];
            sink(1);
            return temp;
        }
        throw 2;
    }
    catch(int e)
    {
        printf("Exception %d: Max Priority Queue is empty\n",e);
    }
}

int MaxPQ::returnMax()
{
    try
    {
        if(!isEmpty()) return elements[1];
        throw 3;
    }
    catch(int e)
    {
        printf("Exception %d: Max Priority Queue is empty\n",e);
    }
}

class MinPQ
{
    public:
    MinPQ();
    bool isEmpty();
    void insert(int k);
    int deleteMin();
    int returnMin();
    protected:
    void swim(int i);
    void sink(int i);
    private:
    int* elements;
    int size;
    int last;
};

MinPQ::MinPQ()
{
    size = PQSize;
    last = 1;
    elements = new int[size];
}

bool MinPQ::isEmpty()
{
    if(last == 1) return true;
    return false;
}

void MinPQ::swim(int i)
{
    while(i>1)
    {
        if(elements[i/2] <= elements[i]) break;
        int temp = elements[i/2];
        elements[i/2] = elements[i];
        elements[i] = temp;
        i /= 2;
    }
}

void MinPQ::sink(int i)
{
    while(true)
    {
        int j = 2*i;
        if(j >= last) break;
        if(j+1 < last) if(elements[j+1] < elements[j]) j++;
        if(elements[j] >= elements[i]) break;
        int temp = elements[i];
        elements[i] = elements[j];
        elements[j] = temp;
        i = j;
    }
}

void MinPQ::insert(int k)
{
    try
    {
        if(last < size)
        {
            elements[last] = k;
            swim(last);
            last++;
        }
        throw 1;
    }
    catch(int e)
    {
        printf("Exception %d: Min Priority Queue is full\n",e);
    }
}

int MinPQ::deleteMin()
{
    try
    {
        if(!isEmpty())
        {
            int temp = elements[1];
            elements[1] = elements[--last];
            sink(1);
            return temp;
        }
        throw 2;
    }
    catch(int e)
    {
        printf("Exception %d: Min Priority Queue is empty\n",e);
    }
}

int MinPQ::returnMin()
{
    try
    {
        if(!isEmpty()) return elements[1];
        throw 3;
    }
    catch(int e)
    {
        printf("Exception %d: Min Priority Queue is empty\n",e);
    }
}

int main()
{
    return 0;
}
