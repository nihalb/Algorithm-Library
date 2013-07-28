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

class Edge
{
    public:
    Edge();
    Edge(Edge& E);
    Edge(int x, int y, double w);
    int Either();
    int Other(int w);
    double Weight();
    Edge& operator= (Edge& E);
    bool operator== (Edge& E);
    private:
    int u;
    int v;
    double weight;
};

Edge::Edge()
{
    u = -1;
    v = -1;
    weight = 0;
}

Edge::Edge(Edge& E)
{
    int x = E.Either();
    int y = E.Other(x);
    u = x;
    v = y;
    weight = E.Weight();
}

Edge::Edge(int x, int y, double w)
{
    u = x;
    v = y;
    weight = w;
}

int Edge::Either()
{
    return u;
}

int Edge::Other(int w)
{
    try
    {
        if(u == w) return v;
        else if(v == w) return u;
        throw 4;
    }
    catch(int e)
    {
        printf("Exception %d: Invalid Vertex\n",e);
    }
}

double Edge::Weight()
{
    return weight;
}

Edge& Edge::operator= (Edge& E)
{
    int x = E.Either();
    int y = E.Other(x);
    u = x;
    v = y;
    weight = E.Weight();
    return *this;
}

bool Edge::operator== (Edge& E)
{
    int x = E.Either();
    int y = E.Other(x);
    return ((x==u && y==v) || (x==v && y==u)) && weight==E.Weight();
}

class WeightedGraph
{
    public:
    WeightedGraph();
    WeightedGraph(int v);
    ~WeightedGraph();
    void AddEdge(Edge E);
    void RemoveEdge(Edge E);
    bool ExistsEdge(Edge E);
    int V();
    int E();
    private:
    int n;
    int m;
    LL<Edge>* Vertices;
};

WeightedGraph::WeightedGraph()
{
    n = m = 0;
}

WeightedGraph::WeightedGraph(int v)
{
    n = v;
    m = 0;
    Vertices = new LL<Edge>[n];
}

WeightedGraph::~WeightedGraph()
{
    delete Vertices;
}

void WeightedGraph::AddEdge(Edge E)
{
    try
    {
        int u = E.Either();
        int v = E.Other(u);
        if(u<n && v<n)
        {
            Vertices[u].insert(E);
            Vertices[v].insert(E);
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

void WeightedGraph::RemoveEdge(Edge E)
{
    try
    {
        int u = E.Either();
        int v = E.Other(u);
        if(u<n && v<n)
        {
            Vertices[u].remove(E);
            Vertices[v].remove(E);
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

bool WeightedGraph::ExistsEdge(Edge E)
{
    try
    {
        int u = E.Either();
        int v = E.Other(u);
        if(u<n && v<n) return Vertices[u].search(E);
        throw 3;
    }
    catch(int e)
    {
        printf("Exception %d: Invalid Edge\n",e);
    }
}

int WeightedGraph::V()
{
    return n;
}

int WeightedGraph::E()
{
    return m;
}

int main()
{
	//freopen(".in","r",stdin);
    WeightedGraph G(5);
    Edge E(0,1,5);
    G.AddEdge(E);
    //G.RemoveEdge(E);
    Edge F(1,2,3);
    printf("%d\n",G.ExistsEdge(E));
    printf("%d\n",G.V());
	return 0;
}
