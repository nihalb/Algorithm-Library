#include<stdio.h>
#include<stack>
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

bool bellman_ford(int s)
{
    // Initialize distances and predecessor pointers
    for(int i=0; i<V; ++i)
    {
        dist[i] = inf;
        prev[i] = -1;
    }
    dist[s] = 0;
    // Perform dynamic programming
    bool update;
    for(int i=1; i<=V; ++i)
    {
        update = false;
        for(int j=0; j<V; ++j)
        {
            for(vector< pair<int,int> >::iterator it = adj_list[j].begin(); it != adj_list[j].end(); ++it)
            {
                int ver = it->first;
                int cost = it->second;
                if(dist[j] + cost < dist[ver])
                {
                    dist[ver] = dist[j] + cost;
                    prev[ver] = j;
                    update = true;
                }
            }
        }
        if(!update && i < V) return true;
    }
    return !update;
}

void get_sp(int s, int d)
{
    for(int i=d; i != -1; i = prev[i]) path.push(i);
}

int main()
{
    V = 4;
    //adj_list[0].push_back(make_pair(3,-1));
    //adj_list[3].push_back(make_pair(0,-1));
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
    bool result = bellman_ford(s);
    if(result)
    {
        get_sp(s,d);
        while(!path.empty())
        {
            printf("%d ",path.top());
            path.pop();
        }
        printf("\n");
        printf("%d\n",dist[d]);
    }
    else printf("Negative cycle found\n");
    
    s=1,d=3;
    result = bellman_ford(s);
    if(result)
    {
        get_sp(s,d);
        while(!path.empty())
        {
            printf("%d ",path.top());
            path.pop();
        }
        printf("\n");
        printf("%d\n",dist[d]);
    }
    else printf("Negative cycle found\n");
    
    return 0;
}
