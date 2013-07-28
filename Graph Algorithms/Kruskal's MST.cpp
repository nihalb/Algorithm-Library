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

class UnionFind
{
    public:
    UnionFind(int n);
    ~UnionFind();
    void Union(int p, int q);
    bool Connected(int p, int q);
    protected:
    int Root(int p);
    private:
    int* Parent;
    int* Weight;
    int n;
};

UnionFind::UnionFind(int n)
{
    this->n = n;
    Parent = new int[n];
    Weight = new int[n];
    for(int i=0; i<n; ++i)
    {
        Parent[i] = i;
        Weight[i] = 1;
    }
}

UnionFind::~UnionFind()
{
    delete[] Parent;
    delete[] Weight;
}

void UnionFind::Union(int p, int q)
{
    int pRoot = Root(p);
    int qRoot = Root(q);
    if(pRoot != qRoot)
    {
        if(Weight[pRoot] < Weight[qRoot])
        {
            Parent[pRoot] = qRoot;
            Weight[qRoot] += Weight[pRoot];
        }
        else
        {
            Parent[qRoot] = pRoot;
            Weight[pRoot] += Weight[qRoot];
        }
    }
}

bool UnionFind::Connected(int p, int q)
{
    return (Root(p)==Root(q));
}

int UnionFind::Root(int p)
{
    int r = Parent[p];
    while(r != Parent[r]) r = Parent[r];
    int i = p;
    int temp;
    while(i != r)
    {
        temp = Parent[i];
        Parent[i] = r;
        i = temp;
    }
    return r;
}

#define MINPQ_SIZE 10000

template <class T>
class MinPQ
{
    public:
    MinPQ();
    bool isEmpty();
    void insert(T k);
    T deleteMin();
    T returnMin();
    protected:
    void swim(int i);
    void sink(int i);
    private:
    T* elements;
    int size;
    int last;
};

template <class T>
MinPQ<T>::MinPQ()
{
    size = MINPQ_SIZE;
    last = 1;
    elements = new T[size];
}

template <class T>
bool MinPQ<T>::isEmpty()
{
    if(last == 1) return true;
    return false;
}

template <class T>
void MinPQ<T>::swim(int i)
{
    while(i>1)
    {
        if(elements[i/2] <= elements[i]) break;
        T temp = elements[i/2];
        elements[i/2] = elements[i];
        elements[i] = temp;
        i /= 2;
    }
}

template <class T>
void MinPQ<T>::sink(int i)
{
    while(true)
    {
        int j = 2*i;
        if(j >= last) break;
        if(j+1 < last) if(elements[j+1] < elements[j]) j++;
        if(elements[j] >= elements[i]) break;
        T temp = elements[i];
        elements[i] = elements[j];
        elements[j] = temp;
        i = j;
    }
}

template <class T>
void MinPQ<T>::insert(T k)
{
	try
	{
		if(last < size)
		{
			elements[last] = k;
			swim(last);
			last++;
			return;
		}
		throw 1;
    }
    catch(int e)
    {
    	printf("Exception %d: Queue is full",e);
    }
}

template <class T>
T MinPQ<T>::deleteMin()
{
	try
    {
    	if(!isEmpty())
		{
			T temp = elements[1];
			elements[1] = elements[--last];
			sink(1);
			return temp;
		}
		throw 2;
    }
	catch(int e)
	{
		printf("Exception %d: Queue is empty",e);
	}
}

template <class T>
T MinPQ<T>::returnMin()
{
	try
    {
    	if(!isEmpty())
		{
			return elements[1];
		}
		throw 3;
    }
    catch(int e)
    {
    	printf("Exception %d: Queue is empty",e);
    }
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
//    Edge& operator= (Edge& E);
    bool operator== (Edge& E);
    bool operator< (Edge& E);
    bool operator> (Edge& E);
    bool operator>= (Edge& E);
    bool operator<= (Edge& E);
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
/*
Edge& Edge::operator= (Edge& E)
{
    int x = E.Either();
    int y = E.Other(x);
    u = x;
    v = y;
    weight = E.Weight();
    return *this;
}*/

bool Edge::operator== (Edge& E)
{
    int x = E.Either();
    int y = E.Other(x);
    return ((x==u && y==v) || (x==v && y==u)) && weight==E.Weight();
}

bool Edge::operator< (Edge& E)
{
	return (this->weight < E.weight);
}

bool Edge::operator> (Edge& E)
{
	return (this->weight > E.weight);
}

bool Edge::operator>= (Edge& E)
{
	return (this->weight >= E.weight);
}

bool Edge::operator<= (Edge& E)
{
	return (this->weight <= E.weight);
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
    double TotalCost();
    WeightedGraph* KruskalMST();
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
    Vertices = new LL<Edge>[n+1];
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
        if(u >= 1 && u <= n && v >= 1 && v <= n)
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
        if(u >= 1 && u <= n && v >= 1 && v <= n)
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
        if(u >= 1 && u <= n && v >= 1 && v <= n) return Vertices[u].search(E);
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

double WeightedGraph::TotalCost()
{
	double cost = 0;
	node<Edge>* iterator;
    for(int i=1; i<=n; ++i)
    {
    	iterator = Vertices[i].head;
    	while(iterator)
    	{
    		cost += (iterator->value).Weight();
    		iterator = iterator->next;
    	}
    }
    return cost/2;
}

WeightedGraph* WeightedGraph::KruskalMST()
{
	WeightedGraph* G = new WeightedGraph(n);

	MinPQ<Edge> PQ;
	node<Edge>* iterator;
	for(int i=1; i<=n; ++i)
	{
		iterator = Vertices[i].head;
		while(iterator)
		{
			PQ.insert(iterator->value);
			iterator = iterator->next;
		}
	}

	UnionFind UF(n+1);
	Edge E;
	int u,v;
	while(!PQ.isEmpty())
	{
		E = PQ.deleteMin();
		u = E.Either();
		v = E.Other(u);
		if(!UF.Connected(u,v))
		{
			G->AddEdge(E);
			UF.Union(u,v);
		}
	}

	return G;
}

// improve api i.e. AddEdge()
// get rid of assignment operator problem
int main()
{
	freopen("edges.txt","r",stdin);
	int n,m;
	int u,v;
	double w;
	scanf("%d%d",&n,&m);
	WeightedGraph G(n);
	Edge* E;
	while(m--)
	{
		scanf("%d%d%lf",&u,&v,&w);
		E = new Edge(u,v,w);
		G.AddEdge(*E);
		delete E;
	}
	WeightedGraph* MST = G.KruskalMST();
	printf("%lf",MST->TotalCost());
	return 0;
}
