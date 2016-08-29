#include<stdio.h>
#include<stack>
#include<set>
#include<utility>
#include<vector>

using namespace std;

const int inf = 1000000000;
const int max_v = 100000+5;

/*
Input:
s -> Source Vertex
V -> Number of Vertices
adj_list -> Adjacency List of Graph

Output:
dist -> Distance array
prev -> Previous array
*/
void dijkstra(int s, int V, vector< pair<int,int> > adj_list[], int* dist, int* prev)
{
    // Initialize priority queue
    set< pair<int,int> > pq;
    dist[s] = 0;
    prev[s] = -1;
    pq.insert(make_pair(0,s));
    for(int i=0; i<V; ++i)
    {
        if(i != s)
        {
            dist[i] = inf;
            prev[i] = -1;
            pq.insert(make_pair(inf,i));
        }
    }    
    // Maintain the invariant
    while(!pq.empty())
    {
        pair<int,int> x = *pq.begin();
        pq.erase(x);
        int u = x.second;
        dist[u] = x.first;
        for(vector< pair<int,int> >::iterator it=adj_list[u].begin(); it != adj_list[u].end(); ++it)
        {
            int ver = it->second;
            int cost = it->first;
            if(dist[u]+cost < dist[ver])
            {
                pq.erase(make_pair(dist[ver],ver));
                dist[ver] = dist[u]+cost;
                prev[ver] = u;
                pq.insert(make_pair(dist[ver],ver));
            }
        }
    }
}

void get_sp(int s, int d, int prev[], stack<int>* path)
{
    for(int i=d; i != -1; i = prev[i]) path->push(i);
}

int main()
{
    vector< pair<int,int> > adj[max_v];
    int distance[max_v];
    int previous[max_v];
    stack<int> path;
    int num_vertices = 4;
    adj[0].push_back(make_pair(1,1));
    adj[0].push_back(make_pair(3,2));
    adj[1].push_back(make_pair(1,0));
    adj[1].push_back(make_pair(1,2));
    adj[1].push_back(make_pair(4,3));
    adj[2].push_back(make_pair(3,0));
    adj[2].push_back(make_pair(1,1));
    adj[2].push_back(make_pair(1,3));
    adj[3].push_back(make_pair(4,1));
    adj[3].push_back(make_pair(1,2));
    
    int s=0,d=3;
    dijkstra(s, num_vertices, adj, distance, previous);
    get_sp(s, d, previous, &path);
    while(!path.empty())
    {
        printf("%d ",path.top());
        path.pop();
    }
    printf("\n");
    printf("%d\n",distance[d]);
    
    s=1,d=3;
    dijkstra(s, num_vertices, adj, distance, previous);
    get_sp(s, d, previous, &path);
    while(!path.empty())
    {
        printf("%d ",path.top());
        path.pop();
    }
    printf("\n");
    printf("%d\n",distance[d]);
    return 0;
}
