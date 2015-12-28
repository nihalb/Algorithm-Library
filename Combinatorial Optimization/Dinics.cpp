#include<stdio.h>
#include<limits.h>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

const int max_v = 1000 + 5;

struct edge
{
    int to;
    int cap;
    int back;
    edge(int t, int c, int b) : to(t), cap(c), back(b) {}
};

int v;
vector<edge> adj_list[max_v];
int level[max_v];
int work[max_v];

void add_edge(int u, int w, int cap)
{
    edge A(w, cap, adj_list[w].size());
    edge B(u, cap, adj_list[u].size());
    adj_list[u].push_back(A);
    adj_list[w].push_back(B);
}

bool level_graph(int s, int t)
{
    // Clear previous level graph
    for(int i=0; i<v; ++i)
    {
        level[i] = -1;
        work[i] = 0;
    }

    // Build new level graph using BFS
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while(!q.empty())
    {
        int c = q.front(); q.pop();
        if(c == t) break;
        for(int i=0; i < adj_list[c].size(); ++i)
        {
            edge curr = adj_list[c][i];
            int j = curr.to;
            int cap = curr.cap;
            if(cap > 0 && level[j] < 0)
            {
                level[j] = level[c] + 1;
                q.push(j);
            }
        }
    }
    return level[t] >= 0;
}

int find_path(int s, int t, int bot)
{
    if(s == t) return bot;
    for(int& i=work[s]; i<adj_list[s].size(); ++i)
    {
        edge& curr = adj_list[s][i];
        int bottleneck;
        if(level[curr.to] == level[s] + 1 && curr.cap > 0 && (bottleneck = find_path(curr.to, t, min(bot, curr.cap))))
        {
            curr.cap -= bottleneck;
            adj_list[curr.to][curr.back].cap += bottleneck;
            return bottleneck;
        }
    }
    return 0;
}

int dinics(int s, int t)
{
    int flow = 0;
    while(level_graph(s,t))
    {
        int bottleneck;
        while(bottleneck = find_path(s, t, INT_MAX)) flow += bottleneck;
    }
    return flow;
}

int main()
{
    return 0;
}
