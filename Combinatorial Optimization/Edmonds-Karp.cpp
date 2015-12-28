#include<stdio.h>
#include<limits.h>
#include<algorithm>
#include<queue>

using namespace std;

const int max_v = 1000 + 5;

int adj_mat[max_v][max_v];
int parent[max_v];
int v;

int bfs(int s, int t, vector<int>& path)
{
    for(int i=0; i<v; ++i) parent[i] = -1;
    queue<int> q;
    q.push(s);
    parent[s] = -2;
   
    while(!q.empty())
    {
        int c = q.front(); q.pop();
        if(c == t) break;
        for(int i=0; i<v; ++i)
        {
            if(adj_mat[c][i] > 0 && parent[i] == -1)
            {
                parent[i] = c;
                q.push(i);
            }
        }
    }

    if(parent[t] == -1) return 0;
    
    int bottleneck = INT_MAX;
    do
    {
        path.push_back(t);
        if(adj_mat[parent[t]][t] < bottleneck) bottleneck = adj_mat[parent[t]][t];
        t = parent[t];
    }
    while(t != s);
    path.push_back(s);
    reverse(path.begin(), path.end());
    return bottleneck;
}

int edmonds_karp(int s, int t)
{
    vector<int> path;
    int bottleneck;
    int flow = 0;
    while(bottleneck = bfs(s, t, path))
    {
        for(int i=1; i<path.size(); ++i)
        {
            adj_mat[path[i-1]][path[i]] -= bottleneck;
            adj_mat[path[i]][path[i-1]] += bottleneck;
        }
        flow += bottleneck;
        path.clear();
    }
    return flow;
}

int main()
{
    return 0;
}
