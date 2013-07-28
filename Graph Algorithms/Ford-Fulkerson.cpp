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

class FlowEdge
{
    public:
    FlowEdge();
    FlowEdge(FlowEdge& E);
    FlowEdge(int x, int y, double c);
    FlowEdge(int x, int y, double c, double f);
    int From();
    int To();
    double Capacity();
    double Flow();
    int Other(int w);
    double ResidualCapacityTo(int w);
    void AddResidualFlowTo(int w, double delta);
    FlowEdge& operator= (FlowEdge& E);
    bool operator== (FlowEdge& E);
    private:
    int u;
    int v;
    double capacity;
    double flow;
};

FlowEdge::FlowEdge()
{
    u = -1;
    v = -1;
    capacity = 0;
    flow = 0;
}

FlowEdge::FlowEdge(FlowEdge& E)
{
    u = E.From();
    v = E.To();
    capacity = E.Capacity();
    flow = E.Flow();
}

FlowEdge::FlowEdge(int x, int y, double c)
{
	try
	{
		if(c >= 0)
		{
			u = x;
			v = y;
			capacity = c;
			flow = 0;
		}
		else throw 1;
	}
	catch(int e)
	{
		printf("Exception %d: Negative edge capacity\n",e);
	}
}

FlowEdge::FlowEdge(int x, int y, double c, double f)
{
	try
	{
		if(c >= 0)
		{
			u = x;
			v = y;
			capacity = c;
			flow = f;
		}
		else throw 2;
	}
	catch(int e)
	{
		printf("Exception %d: Negative edge capacity\n",e);
	}
}

int FlowEdge::From()
{
	return u;
}

int FlowEdge::To()
{
    return v;
}

double FlowEdge::Capacity()
{
    return capacity;
}

double FlowEdge::Flow()
{
    return flow;
}

int FlowEdge::Other(int w)
{
	try
	{
		if(w == u) return v;
		else if(w == v) return u;
		else throw 3;
	}
	catch(int e)
	{
		printf("Exception %d: Illegal endpoint\n",e);
	}
}

double FlowEdge::ResidualCapacityTo(int w)
{
	try
	{
		if(w == u) return flow;
		else if(w == v) return capacity-flow;
		else throw 4;
	}
	catch(int e)
	{
		printf("Exception %d: Illegal endpoint\n",e);
	}
}

void FlowEdge::AddResidualFlowTo(int w, double delta)
{
	try
	{
		if(w == u) flow -= delta;
		else if(w == v) flow += delta;
		else throw 5;
	}
	catch(int e)
	{
		printf("Exception %d: Illegal endpoint\n",e);
	}
}

FlowEdge& FlowEdge::operator= (FlowEdge& E)
{
    u = E.From();
    v = E.To();
    capacity = E.Capacity();
    flow = E.Flow();
    return *this;
}

bool FlowEdge::operator== (FlowEdge& E)
{
    return u == E.From() && v == E.To() && capacity == E.Capacity() && flow == E.Flow();
}

class FlowNetwork
{
    public:
    FlowNetwork();
    FlowNetwork(int v);
    ~FlowNetwork();
    void AddEdge(FlowEdge* E);
    int V();
    int E();
    double FordFulkerson(int s, int t);
    protected:
	bool HasAugmentingPath(FlowEdge** &EdgeTo, int s, int t);
    private:
    int n;
    int m;
    LL<FlowEdge*>* Vertices;
};

FlowNetwork::FlowNetwork()
{
    n = m = 0;
}

FlowNetwork::FlowNetwork(int v)
{
    n = v;
    m = 0;
    Vertices = new LL<FlowEdge*>[n];
}

FlowNetwork::~FlowNetwork()
{
    delete Vertices;
}

void FlowNetwork::AddEdge(FlowEdge* E)
{
    try
    {
        int u = E->From();
        int v = E->To();
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

int FlowNetwork::V()
{
    return n;
}

int FlowNetwork::E()
{
    return m;
}

bool FlowNetwork::HasAugmentingPath(FlowEdge** &EdgeTo, int s, int t)
{
	queue<int> Q;
	bool* Marked = new bool[n];

	for(int i=0; i<n; ++i) Marked[i] = false;

	Q.push(s);
	Marked[s] = true;

	int u,v;
	FlowEdge* e;
	node<FlowEdge*>* iterator;

	while(!Q.isEmpty())
	{
		u = Q.pop();
		iterator = Vertices[u].head;
		while(iterator != NULL)
		{
			e = iterator->value;
			v = e->Other(u);
			if(e->ResidualCapacityTo(v) > 0)
			{
				if(!Marked[v])
				{
					Marked[v] = true;
					EdgeTo[v] = e;
					Q.push(v);
				}
			}
			iterator = iterator->next;
		}
	}

	bool result = Marked[t];

	delete[] Marked;

	return result;
}

double FlowNetwork::FordFulkerson(int s, int t)
{
	double MaxFlow = 0;

	FlowEdge** EdgeTo = new FlowEdge*[n];
	for(int i=0; i<n; ++i) EdgeTo[i] = NULL;

	FlowEdge* ResidualEdge;
	int u,v;
	double bottleneck;

	while(HasAugmentingPath(EdgeTo,s,t))
	{
		v = t;
		ResidualEdge = EdgeTo[v];
		u = ResidualEdge->Other(v);
		bottleneck = ResidualEdge->ResidualCapacityTo(v);

		while(u != s)
		{
			v = u;
			ResidualEdge = EdgeTo[v];
			u = ResidualEdge->Other(v);
			if(ResidualEdge->ResidualCapacityTo(v) < bottleneck)
			{
				bottleneck = ResidualEdge->ResidualCapacityTo(v);
			}
		}

		v = t;
		ResidualEdge = EdgeTo[v];
		u = ResidualEdge->Other(v);
		ResidualEdge->AddResidualFlowTo(v,bottleneck);

		while(u != s)
		{
			v = u;
			ResidualEdge = EdgeTo[v];
			u = ResidualEdge->Other(v);
			ResidualEdge->AddResidualFlowTo(v,bottleneck);
		}

		MaxFlow += bottleneck;
	}

	delete[] EdgeTo;

	return MaxFlow;
}

int main()
{
	freopen("FlowNetwork.txt","r",stdin);

	int n,m;

	printf("Enter the number of vertices in the Flow Network\n");
	scanf("%d",&n);

	FlowNetwork N(n);

	int s,t;
	printf("Enter the source and sink in the Flow Network\n");
	scanf("%d%d",&s,&t);

	printf("Enter the number of edges in the Flow Network\n");
	scanf("%d",&m);

	printf("Enter the edges and their capacity\n");

	FlowEdge* F;
	int u,v;
	double c;

	while(m--)
	{
		scanf("%d%d%lf",&u,&v,&c);
		F = new FlowEdge(u-1,v-1,c);
		N.AddEdge(F);
	}

	printf("The maximum flow through the Flow Network is: %lf\n",N.FordFulkerson(s-1,t-1));

	return 0;
}
