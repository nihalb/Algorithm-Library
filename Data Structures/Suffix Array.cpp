#include<stdio.h>
#include<algorithm>

using namespace std;

struct rank
{
    int index;
    int first;
    int second;
};

bool less_rank(rank A, rank B)
{
    if(A.first == B.first) return A.second < B.second;
    else return A.first < B.first;
}

const int max_n = 100000+5;
const int max_l = 18;
int len,steps;
char str[max_n];
int P[max_l][max_n];
rank R[max_n];

void manber_myers()
{
    int count;

    for(len=0; str[len] != '\0'; ++len) P[0][len] = str[len];

    for(steps=1,count=1; count>>1 < len; steps++,count<<=1)
    {
        for(int i=0; i<len; ++i)
        {
            R[i].index = i;
            R[i].first = P[steps-1][i];
            R[i].second = (i+count < len)?P[steps-1][i+count]:-1;
        }

        sort(R,R+len,less_rank);

        P[steps][R[0].index] = 0;
        for(int i=1; i<len; ++i)
        {
            if(R[i].first == R[i-1].first && R[i].second == R[i-1].second) P[steps][R[i].index] = P[steps][R[i-1].index];
            else P[steps][R[i].index] = i;
        }
    }
}

int lcp(int i, int j)
{
    if(i == j) return len - i;
    int ans = 0;
    for(int k=steps-1; k>=0 && i<len && j<len; --k)
    {
        if(P[k][i] == P[k][j])
        {
            i += 1<<k;
            j += 1<<k;
            ans += 1<<k;
        }
    }
    return ans;
}

int main()
{
    scanf("%s",str);

    manber_myers();

    for(int i=0; i<len; ++i) printf("%d\n",R[i].index);

    return 0;
}
