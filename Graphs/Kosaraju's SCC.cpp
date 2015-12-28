#include<stdio.h>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

const int max_v = 100000 + 5;

int v;
vector<int> adj_list[max_v];
vector<int> rev_adj_list[max_v];

bool visited[max_v];
int scc[max_v];

void dfs_rev(int i, stack<int>& s)
{
    if(visited[i]) return;
    visited[i] = true;
    for(int j=0; j<rev_adj_list[i].size(); ++j) dfs_rev(rev_adj_list[i][j], s);
    s.push(i);
}

stack<int> reverse_dfs_order()
{
    stack<int> s;
    for(int i=0; i<v; ++i) visited[i] = false;
    for(int i=0; i<v; ++i) if(!visited[i]) dfs_rev(i, s);
    return s;
}

void dfs_fill(int i, int component)
{
    if(visited[i]) return;
    visited[i] = true;
    scc[i] = component;
    for(int j=0; j<adj_list[i].size(); ++j) dfs_fill(adj_list[i][j], component);
}

void kosaraju_scc()
{
    // Compute reverse graph
    for(int i=0; i<v; ++i) for(int j=0; j<adj_list[i].size(); ++j) rev_adj_list[adj_list[i][j]].push_back(i);
    stack<int> s = reverse_dfs_order();

    // DFS graph in the computed order
    int component = 0;
    for(int i=0; i<v; ++i) visited[i] = false;
    while(!s.empty())
    {
        int curr = s.top();
        s.pop();
        if(!visited[curr])
        {
            dfs_fill(curr, component);
            component++;
        }
    }
}

int main()
{
    v = 3;
    adj_list[0].push_back(1);
    adj_list[1].push_back(0);
    adj_list[1].push_back(2);
    kosaraju_scc();
    for(int i=0; i<v; ++i) printf("scc[%d] = %d\n", i, scc[i]);
    return 0;
}
