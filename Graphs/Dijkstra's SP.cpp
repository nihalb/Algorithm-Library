#include<stdio.h>
#include<stack>
#include<set>
#include<utility>
#include<vector>

using namespace std;

const int inf = 1000000000;
const int max_v = 100000+5;
vector< pair<int,int> > adj_list[max_v];
int dist[max_v];
int prev[max_v];
stack<int> path;

int V,E;

void dijkstra(int s)
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
            int ver = it->first;
            int cost = it->second;
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

void get_sp(int s, int d)
{
    for(int i=d; i != -1; i = prev[i]) path.push(i);
}

int main()
{
    V = 4;
    adj_list[0].push_back(make_pair(1,1));
    adj_list[0].push_back(make_pair(2,3));
    adj_list[1].push_back(make_pair(0,1));
    adj_list[1].push_back(make_pair(2,1));
    adj_list[1].push_back(make_pair(3,4));
    adj_list[2].push_back(make_pair(0,3));
    adj_list[2].push_back(make_pair(1,1));
    adj_list[2].push_back(make_pair(3,1));
    adj_list[3].push_back(make_pair(1,4));
    adj_list[3].push_back(make_pair(2,1));
    
    int s=0,d=3;
    dijkstra(s);
    get_sp(s,d);
    while(!path.empty())
    {
        printf("%d ",path.top());
        path.pop();
    }
    printf("\n");
    printf("%d\n",dist[d]);
    
    s=1,d=3;
    dijkstra(s);
    get_sp(s,d);
    while(!path.empty())
    {
        printf("%d ",path.top());
        path.pop();
    }
    printf("\n");
    printf("%d\n",dist[d]);
    return 0;
}
