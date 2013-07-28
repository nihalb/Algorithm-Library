#include<stdio.h>
#include<algorithm>

struct Rank
{
	int index;
	int first;
	int second;
};

bool LessRank(Rank A, Rank B)
{
	if(A.first == B.first)
	{
		return A.second < B.second;
	}
	else
	{
		return A.first < B.first;
	}
}

const int MaxN = 100000+5;
const int MaxL = 18;
int len,steps;
char str[MaxN];
int P[MaxL][MaxN];
Rank R[MaxN];

void ManberMyers()
{
	int count;

	for(len=0; str[len] != '\0'; ++len)
	{
		P[0][len] = str[len];
	}

	for(steps=1,count=1; count>>1 < len; steps++,count<<=1)
	{
		for(int i=0; i<len; ++i)
		{
			R[i].index = i;
			R[i].first = P[steps-1][i];
			R[i].second = (i+count < len)?P[steps-1][i+count]:-1;
		}

		std::sort(R,R+len,LessRank);

		P[steps][R[0].index] = 0;
		for(int i=1; i<len; ++i)
		{
			if(R[i].first == R[i-1].first && R[i].second == R[i-1].second)
			{
				P[steps][R[i].index] = P[steps][R[i-1].index];
			}
			else
			{
				P[steps][R[i].index] = i;
			}
		}
	}
}

int LCP(int i, int j)
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

	ManberMyers();

	for(int i=0; i<len; ++i)
	{
		printf("%d\n",R[i].index);
	}

	return 0;
}
