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
    set<EDGE> pq;
    vector< vector<EDGE> > mst(v);

    // Initialize priority queue
    pq.insert(make_pair(0,0));
    score[0] = 0;
    for(int i=1; i<v; ++i)
        pq.insert(make_pair(INF,i));

    // Maintain the invariant
    while(!pq.empty())
    {
        EDGE x = *pq.begin();
        pq.erase(x);
        int c = x.first;
        int u = x.second;
        visited[u] = true;
        if(pred[u] != -1)
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
                    pq.erase(make_pair(score[w],w));
                    score[w] = cost;
                    pred[w] = u;
                    pq.insert(make_pair(score[w],w));
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
    
    // Run Prim's and get MST cost
    vector< vector<EDGE> > mst = prim(adj_list);
    int mst_cost = 0;
    for(int i=0; i<mst.size(); ++i)
        for(vector<EDGE>::iterator it = mst[i].begin(); it != mst[i].end(); ++it)
            mst_cost += it->second;
    mst_cost /= 2;

    // Check if the cost is correct
    assert(mst_cost == 3);

    return 0;
}
