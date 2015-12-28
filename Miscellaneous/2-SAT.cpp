#include<stdio.h>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

const int max_n = 100000 + 5;
int n;

const int max_v = 200000 + 5;
int v;

vector<int> adj_list[max_v];
vector<int> rev_adj_list[max_v];

bool visited[max_v];
int scc[max_v];
int leader[max_v];
bool assignment[max_v];
bool assigned[max_v];

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
    visited[i] = true;
    scc[i] = component;
    for(int j=0; j<adj_list[i].size(); ++j)
    {
        int u = adj_list[i][j];
        if(!visited[u])
        {
            leader[u] = leader[i];
            dfs_fill(u, component);
        }
    }
}

int negated(int x)
{
    return (x < n) ? (x + n) : (x - n);
}

bool two_sat()
{
    // Compute reverse graph
    for(int i=0; i<v; ++i) for(int j=0; j<adj_list[i].size(); ++j) rev_adj_list[adj_list[i][j]].push_back(i);
    stack<int> s = reverse_dfs_order();

    // DFS graph in the computed order to get SCC
    int component = 0;
    vector<int> order;
    for(int i=0; i<v; ++i) visited[i] = false;
    while(!s.empty())
    {
        int curr = s.top();
        s.pop();
        order.push_back(curr);
        if(!visited[curr])
        {
            leader[curr] = curr;
            dfs_fill(curr, component);
            component++;
        }
    }

    // Check if an assignment exists
    for(int i=0; i<n; ++i) if(scc[i] == scc[i+n]) return false;

    // Iterate over components in topological order and assign false
    for(int i=0; i<v; ++i) assigned[i] = false;
    for(int i=v-1; i>=0; --i)
    {
        int u = order[i];
        int l = leader[u];
        if(!assigned[l])
        {
            assigned[l] = true;
            assignment[l] = false;
            assigned[leader[negated(l)]] = true;
            assignment[leader[negated(l)]] = true;
        }
    }

    return true;
}

// Adds clause x v y
void add_clause(int x, int y)
{
    adj_list[negated(x)].push_back(y);
    adj_list[negated(y)].push_back(x);
}

bool get_assignment(int x)
{
    return assignment[leader[x]];
}

int main()
{
    n = 2;
    v = 2 * n;
    add_clause(0, 1);
    add_clause(2, 1);
    add_clause(2, 3);
    bool satisfied = two_sat();
    if(satisfied) for(int i=0; i<n; ++i) printf("var %d = %d\n", i, get_assignment(i));
    else printf("Formula is not satisfiable\n");
    return 0;
}
