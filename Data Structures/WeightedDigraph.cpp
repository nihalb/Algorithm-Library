#include<stdio.h>

template <class T>
struct node
{
	T value;
	node* next;
};

template <class T>
class LL
{
    public:
    LL();
    void insert(T k);
    void remove(T k);
    bool search(T k);
    node<T>* head;
    node<T>* last;
};

template <class T>
LL<T>::LL()
{
    head = last = NULL;
}

template <class T>
void LL<T>::insert(T k)
{
    node<T>* temp = new node<T>();
    temp->value = k;
    temp->next = NULL;
    if(head) last = last->next = temp;
    else head = last = temp;
}

template <class T>
void LL<T>::remove(T k)
{
    node<T>* p = NULL;
    node<T>* n = head;
    while(n)
    {
        if(n->value == k)
        {
            if(n == head)
            {
                head = n->next;
                if(!head) last = NULL;
            }
            else
            {
                p->next = n->next;
                if(!(p->next)) last = p;
            }
            delete n;
            return;
        }
        p = n;
        n = n->next;
    }
}

template <class T>
bool LL<T>::search(T k)
{
    node<T>* temp = head;
    while(temp)
    {
        if(temp->value == k) break;
        else temp = temp->next;
    }
    return (temp != NULL);
}

class DirectedEdge
{
    public:
    DirectedEdge();
    DirectedEdge(DirectedEdge& E);
    DirectedEdge(int x, int y, double w);
    int From();
    int To();
    double Weight();
    DirectedEdge& operator= (DirectedEdge& E);
    bool operator== (DirectedEdge& E);
    private:
    int u;
    int v;
    double weight;
};

DirectedEdge::DirectedEdge()
{
    u = -1;
    v = -1;
    weight = 0;
}

DirectedEdge::DirectedEdge(DirectedEdge& E)
{
    u = E.From();
    v = E.To();
    weight = E.Weight();
}

DirectedEdge::DirectedEdge(int x, int y, double w)
{
    u = x;
    v = y;
    weight = w;
}

int DirectedEdge::From()
{
	return u;
}

int DirectedEdge::To()
{
    return v;
}

double DirectedEdge::Weight()
{
    return weight;
}

DirectedEdge& DirectedEdge::operator= (DirectedEdge& E)
{
    u = E.From();
    v = E.To();
    weight = E.Weight();
    return *this;
}

bool DirectedEdge::operator== (DirectedEdge& E)
{
    return u == E.From() && v == E.To() && weight == E.Weight();
}

class WeightedDigraph
{
    public:
    WeightedDigraph();
    WeightedDigraph(int v);
    ~WeightedDigraph();
    void AddEdge(DirectedEdge E);
    void RemoveEdge(DirectedEdge E);
    bool ExistsEdge(DirectedEdge E);
    int V();
    int E();
    private:
    int n;
    int m;
    LL<DirectedEdge>* Vertices;
};

WeightedDigraph::WeightedDigraph()
{
    n = m = 0;
}

WeightedDigraph::WeightedDigraph(int v)
{
    n = v;
    m = 0;
    Vertices = new LL<DirectedEdge>[n];
}

WeightedDigraph::~WeightedDigraph()
{
    delete Vertices;
}

void WeightedDigraph::AddEdge(DirectedEdge E)
{
    try
    {
        int u = E.From();
        int v = E.To();
        if(u<n && v<n)
        {
            Vertices[u].insert(E);
            m++;
            return;
        }
        throw 1;
    }
    catch(int e)
    {
        printf("Exception %d: Invalid Edge\n",e);
    }
}

void WeightedDigraph::RemoveEdge(DirectedEdge E)
{
    try
    {
        int u = E.From();
        int v = E.To();
        if(u<n && v<n)
        {
            Vertices[u].remove(E);
            m--;
            return;
        }
        throw 2;
    }
    catch(int e)
    {
        printf("Exception %d: Invalid Edge\n",e);
    }
}

bool WeightedDigraph::ExistsEdge(DirectedEdge E)
{
    try
    {
        int u = E.From();
        int v = E.To();
        if(u<n && v<n) return Vertices[u].search(E);
        throw 3;
    }
    catch(int e)
    {
        printf("Exception %d: Invalid Edge\n",e);
    }
}

int WeightedDigraph::V()
{
    return n;
}

int WeightedDigraph::E()
{
    return m;
}

int main()
{
	WeightedDigraph G(5);
    DirectedEdge E(0,1,5);
    G.AddEdge(E);
    DirectedEdge F(1,0,5);
    printf("%d\n",G.ExistsEdge(F));
    printf("%d\n",G.V());
	return 0;
}
