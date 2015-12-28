#include<stdio.h>

using namespace std;

const int max_l = 1000 + 5;
const int max_r = 1000 + 5;

int graph[max_l][max_r];
int match_l[max_l];
int match_r[max_r];
int seen[max_l];
int l,r;

bool bpm(int u)
{
    if(seen[u]) return false;
    seen[u] = 1;
    for(int w=0; w<r; ++w)
    {
        if(graph[u][w])
        {
            if(match_r[w] == -1 || bpm(match_r[w]))
            {
                match_l[u] = w;
                match_r[w] = u;
                return true;
            }
        }
    }
    return false;
}

int matchings()
{
    int matches = 0;
    for(int i=0; i<l; ++i) match_l[i] = -1;
    for(int i=0; i<r; ++i) match_r[i] = -1;
    for(int i=0; i<l; ++i)
    {
        for(int j=0; j<l; ++j) seen[j] = 0;
        if(bpm(i)) matches++;
    }
    return matches;
}

int main()
{
    return 0;
}
