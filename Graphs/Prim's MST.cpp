#include<stdio.h>
#include<set>
#include<utility>
#include<vector>
#include<assert.h>

using namespace std;

/*
    EDGE.first is the vertex
    EDGE.second is the cost
*/
typedef pair<int,int> EDGE;

struct second_cmp
{
    bool operator() (const EDGE& l, const EDGE& r) const
    {
        if(l.second != r.second) return l.second < r.second;
        else return l.first < r.first;
    }
};

/*
    Uses Prim's algorithm to obtain a MST. Assumes graph is connected.

    @param graph adjacency list of the graph where each list contains (vertex, cost) pairs
    @return adjacency list of an MST where each list contains (vertex, cost) pairs
*/
vector< vector<EDGE> > prim(vector< vector<EDGE> >& graph)
{
    const int INF = 1e9;
    int v = graph.size();
    vector<int> score(v,INF);
    vector<int> pred(v,-1);
    vector<bool> visited(v,false);
    set<EDGE,second_cmp> pq;
    vector< vector<EDGE> > mst(v);

    // Initialize priority queue
    score[0] = 0;
    for(int i=0; i<v; ++i)
        pq.insert(make_pair(i,score[i]));

    // Maintain the invariant
    while(!pq.empty())
    {
        EDGE x = *pq.begin();
        pq.erase(x);
        int u = x.first;
        int c = x.second;
        visited[u] = true;
        if(u != 0)
        {
            mst[pred[u]].push_back(make_pair(u,c));
            mst[u].push_back(make_pair(pred[u],c));
        }
        for(vector<EDGE>::iterator it=graph[u].begin(); it != graph[u].end(); ++it)
        {
            int w = it->first;
            int cost = it->second;
            if(!visited[w])
            {
                if(cost < score[w])
                {
                    pq.erase(make_pair(w,score[w]));
                    score[w] = cost;
                    pred[w] = u;
                    pq.insert(make_pair(w,score[w]));
                }
            }
        }
    }

    return mst;
}

int main()
{
    // TEST CASE

    // Define graph
    vector< vector< EDGE > > adj_list(4);
    adj_list[0].push_back(make_pair(1,10));
    adj_list[1].push_back(make_pair(0,10));
    adj_list[0].push_back(make_pair(2,5));
    adj_list[2].push_back(make_pair(0,5));
    adj_list[1].push_back(make_pair(2,15));
    adj_list[2].push_back(make_pair(1,15));
    adj_list[3].push_back(make_pair(1,2));
    adj_list[1].push_back(make_pair(3,2));
    adj_list[3].push_back(make_pair(2,40));
    adj_list[2].push_back(make_pair(3,40));
    
    // Run Prim's and get MST cost
    vector< vector<EDGE> > mst = prim(adj_list);
    int mst_cost = 0;
    for(int i=0; i<mst.size(); ++i)
        for(vector<EDGE>::iterator it = mst[i].begin(); it != mst[i].end(); ++it)
            mst_cost += it->second;
    mst_cost /= 2;

    // Check if the cost is correct
    assert(mst_cost == 17);

    return 0;
}
