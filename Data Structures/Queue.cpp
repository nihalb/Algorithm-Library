#include<stdio.h>
#define _MAX_QUEUE_SIZE_ 1000

template <class T>
class queue
{
    public:
    queue();
    ~queue();
    void push(T n);
    T pop();
    bool isEmpty();
    bool isFull();
    private:
    T* data;
    int size;
    int head;
    int tail;
    int filled;
};

template <class T>
queue<T>::queue()
{
    size = _MAX_QUEUE_SIZE_;
    data = new T[size];
    filled = 0;
    tail = 0;
    head = 0;
}

template <class T>
queue<T>::~queue()
{
    delete[] data;
}

template <class T>
void queue<T>::push(T n)
{
    try
    {
        if(filled != size)
        {
            data[tail++] = n;
            filled++;
            if(tail == size) tail = 0;
            return;
        }
        throw -1;
    }
    catch(int e)
    {
        printf("Exception: Queue is full\n");
    }
}

template <class T>
T queue<T>::pop()
{
    try
    {
        if(filled != 0)
        {
            T temp = data[head++];
            filled--;
            if(head == size) head = 0;
            return temp;
        }
        throw -1;
    }
    catch(int e)
    {
        printf("Exception: Queue is empty\n");
    }
}

template <class T>
bool queue<T>::isEmpty()
{
    return (filled==0);
}

template <class T>
bool queue<T>::isFull()
{
    return (filled==size);
}

int main()
{
    return 0;
}
