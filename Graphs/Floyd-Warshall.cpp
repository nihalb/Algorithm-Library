#include<stdio.h>
#include<limits.h>
#include<algorithm>

#define int64 long long

using namespace std;

const int max_v = 100 + 5;

int64 adj_mat[max_v][max_v];

int64 dist[max_v][max_v];
int pred[max_v][max_v];

int v;

void floyd_warshall()
{
    for(int i=0; i<v; ++i)
    {
        for(int j=0; j<v; ++j)
        {
            dist[i][j] = (adj_mat[i][j] == 0) ? INT_MAX : adj_mat[i][j];
            pred[i][j] = -1;
        }
        if(dist[i][i] > 0) dist[i][i] = 0;
    }
    for(int k=0; k<v; ++k)
    {
        for(int i=0; i<v; ++i)
        {
            for(int j=0; j<v; ++j)
            {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = k;
                }
            }
        }
    }
}

int main()
{
    return 0;
}
