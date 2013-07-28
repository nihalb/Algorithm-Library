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

#define PQ_SIZE 10000

template <class T>
class IndexMinPQ
{
    public:
    IndexMinPQ(int n);
    bool isEmpty();
    void insert(int n, T k);
    T deleteMin();
    T returnMin();
    bool contains(int i);
    void update(int i, T k);
    void decreaseKey(int i, T k);
    protected:
    void swim(int i);
    void sink(int i);
    void exchange(int i, int j);
    private:
    T keys[PQ_SIZE];
    int pq[PQ_SIZE];
    int qp[PQ_SIZE];
    int size;
    int last;
};

template <class T>
IndexMinPQ<T>::IndexMinPQ(int n)
{
    size = n;
    for(int i=1; i<=size; ++i) qp[i] = -1;
    last = 1;
}

template <class T>
bool IndexMinPQ<T>::isEmpty()
{
    if(last == 1) return true;
    return false;
}

template <class T>
void IndexMinPQ<T>::swim(int i)
{
    while(i>1)
    {
        if(keys[i/2] <= keys[i]) break;
        T temp = keys[i/2];
        keys[i/2] = keys[i];
        keys[i] = temp;
		exchange(i,i/2);
        i /= 2;
    }
}

template <class T>
void IndexMinPQ<T>::sink(int i)
{
    while(true)
    {
        int j = 2*i;
        if(j >= last) break;
        if(j+1 < last) if(keys[j+1] < keys[j]) j++;
        if(keys[j] >= keys[i]) break;
        T temp = keys[i];
        keys[i] = keys[j];
        keys[j] = temp;
        exchange(i,j);
        i = j;
    }
}

template <class T>
void IndexMinPQ<T>::exchange(int i, int j)
{
	int temp = pq[i];
	pq[i] = pq[j];
	pq[j] = temp;
	qp[pq[i]] = i;
	qp[pq[j]] = j;
}

template <class T>
void IndexMinPQ<T>::insert(int n, T k)
{
    keys[last] = k;
    pq[last] = n;
    qp[n] = last;
    swim(last);
    last++;
}

template <class T>
T IndexMinPQ<T>::deleteMin()
{
	try
	{
		if(!isEmpty())
		{
			T temp = keys[1];
			qp[pq[1]] = -1;
			keys[1] = keys[--last];
			pq[1] = pq[last];
			qp[pq[1]] = 1;
			sink(1);
			return temp;
		}
		throw 1;
	}
	catch(int e)
	{
		printf("Exception %d: Queue is empty\n",e);
	}
}

template <class T>
T IndexMinPQ<T>::returnMin()
{
	try
	{
	    if(!isEmpty()) return keys[1];
	    throw 2;
	}
    catch(int e)
	{
		printf("Exception %d: Queue is empty\n",e);
	}
}

template <class T>
bool IndexMinPQ<T>::contains(int i)
{
	try
	{
		if(i>=1 && i<=size) return (qp[i] != -1);
		throw 3;
	}
	catch(int e)
	{
		printf("Exception %d: Index out of range\n",e);
	}
}

template <class T>
void IndexMinPQ<T>::update(int i, T k)
{
	try
	{
		if(contains(i))
		{
			int index = qp[i];
			keys[index] = k;
			swim(index);
			sink(index);
			return;
		}
		throw 4;
	}
	catch(int e)
	{
		printf("Exception %d: Element not contained in queue\n",e);
	}
}

template <class T>
void IndexMinPQ<T>::decreaseKey(int i, T k)
{
	try
	{
		if(contains(i))
		{
			int index = qp[i];
			if(keys[index] > k)
			{
				keys[index] = k;
				swim(index);
			}
			return;
		}
		throw 4;
	}
	catch(int e)
	{
		printf("Exception %d: Element not contained in queue\n",e);
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
    WeightedGraph* PrimMST();
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

WeightedGraph* WeightedGraph::PrimMST()
{
	WeightedGraph* G = new WeightedGraph(n);

	bool* covered = new bool[n + 1];
	for(int i=1; i<=n; ++i) covered[i] = false;

	double INFINITY = 1000000000.0;

	IndexMinPQ<Edge> PQ(n);

	// Initialize the priority queue
	Edge* E;
	for(int i=2; i<=n; ++i)
	{
		E = new Edge(1,1,INFINITY);
		PQ.insert(i,*E);
		delete E;
	}

	Edge temp;
	int v;
	node<Edge>* iterator = Vertices[1].head;
	while(iterator)
	{
		temp = iterator->value;
		v = temp.Other(1);
		PQ.decreaseKey(v,temp);
		iterator = iterator->next;
	}
	covered[1] = true;

	// Maintain the invariant
	int w;
	while(!PQ.isEmpty())
	{
		temp = PQ.deleteMin();
		G->AddEdge(temp);
		v = temp.Either();
		if(covered[v]) v = temp.Other(v);
		iterator = Vertices[v].head;
		while(iterator)
		{
			temp = iterator->value;
			w = temp.Other(v);
			if(!covered[w]) PQ.decreaseKey(w,temp);
			iterator = iterator->next;
		}
		covered[v] = true;
	}

	delete[] covered;

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
	WeightedGraph* MST = G.PrimMST();
	printf("%lf",MST->TotalCost());
	return 0;
}
