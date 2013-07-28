#include<stdio.h>

class stack
{
    public:
    stack();
    ~stack();
    void push(int n);
    int pop();
    bool isEmpty();
    private:
    int* data;
    int size;
    int current;
};

stack::stack()
{
    size = 1;
    current = 0;
    data = new int[1];
}

stack::~stack()
{
    delete[] data;
}

void stack::push(int n)
{
    if(current == size)
    {
        int* temp = new int[2*size];
        for(int i=0; i<size; ++i) temp[i] = data[i];
        delete data;
        data = temp;
        size *= 2;
    }
    data[current++] = n;
}

int stack::pop()
{
    try
    {
        if(!isEmpty())
        {
            int item = data[--current];
            if(current > 0 && current == size/4)
            {
                int* temp = new int[size/2];
                for(int i=0; i<size/4; ++i) temp[i] = data[i];
                delete data;
                data = temp;
                size /= 2;
            }
            return item;
        }
        throw -1;
    }
    catch(int e)
    {
        printf("Exception: Stack is empty\n");
    }
}

bool stack::isEmpty()
{
    return (current == 0);
}

int main()
{
    return 0;
}
