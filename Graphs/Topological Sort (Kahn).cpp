#include<stdio.h>
#include<algorithm>
#include<set>
#include<vector>

using namespace std;

const int max_v = 100000 + 5;

int v;
vector<int> adj_list[max_v];
int in_degree[max_v];

// Returns a vector of vertices if there is no negative cycle
// Else returns an empty vector
// Set s can be replaced by any collection like stack, queue, priority queue, etc
vector<int> topological_sort()
{
    for(int i=0; i<v; ++i) in_degree[i] = 0;
    for(int i=0; i<v; ++i) for(int j=0; j<adj_list[i].size(); ++j) in_degree[adj_list[i][j]]++;
    set<int> s;
    vector<int> l;
    for(int i=0; i<v; ++i) if(in_degree[i] == 0) s.insert(i);
    while(!s.empty())
    {
        set<int>::iterator it = s.begin();
        int u = *it;
        s.erase(it);
        l.push_back(u);
        for(int i=0; i<adj_list[u].size(); ++i)
        {
            int w = adj_list[u][i];
            in_degree[w]--;
            if(in_degree[w] == 0) s.insert(w);
        }
    }
    for(int i=0; i<v; ++i) if(in_degree[i] > 0) return vector<int>();
    return l;
}

int main()
{
    v = 3;
    adj_list[0].push_back(1);
    adj_list[1].push_back(2);
    vector<int> s = topological_sort();
    if(s.size() == 0) printf("Negative cycle found\n");
    else for(int i=0; i<v; ++i) printf("%d\n", s[i]);

    adj_list[2].push_back(0);
    s = topological_sort();
    if(s.size() == 0) printf("Negative cycle found\n");
    else for(int i=0; i<v; ++i) printf("%d\n", s[i]);
    return 0;
}
