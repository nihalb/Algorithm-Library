#include<stdio.h>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

const int max_v = 100000 + 5;

int v;
vector<int> adj_list[max_v];

int visited[max_v];

bool dfs(int i, stack<int>& s)
{
    if(visited[i] == 2) return true;
    if(visited[i] == 1) return false;
    visited[i] = 1;
    for(int j=0; j<adj_list[i].size(); ++j) if(!dfs(adj_list[i][j], s)) return false;
    visited[i] = 2;
    s.push(i);
    return true;
}

// Returns a stack of vertices if there is no negative cycle
// Else returns an empty stack
stack<int> topological_sort()
{
    stack<int> s;
    for(int i=0; i<v; ++i) visited[i] = 0;
    for(int i=0; i<v; ++i) if(!visited[i]) if(!dfs(i, s)) return stack<int>();
    return s;
}

int main()
{
    v = 3;
    adj_list[0].push_back(1);
    adj_list[1].push_back(2);
    stack<int> s = topological_sort();
    if(s.empty()) printf("Negative cycle found\n");
    while(!s.empty())
    {
        printf("%d\n", s.top());
        s.pop();
    }

    adj_list[2].push_back(0);
    if(s.empty()) printf("Negative cycle found\n");
    while(!s.empty())
    {
        printf("%d\n", s.top());
        s.pop();
    }
    return 0;
}
