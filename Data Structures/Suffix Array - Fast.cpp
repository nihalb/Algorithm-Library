#include<stdio.h>

const int MaxN = 100000+5;

char str[MaxN];                 // contains the string
int len;                        // denotes the length of the string
int suffix[MaxN];               // suffix[i] = index of the suffix at rank i
int inverse[MaxN];              // inverse[i] = rank of the i-th suffix
bool BH[MaxN];                  // BH[i] = true only if i is the first suffix in its h-bucket
int next[MaxN];                 // next[i] = the first index to occur after the i's bucket
int count[MaxN];
bool B2H[MaxN];

int lcp[MaxN];                  // lcp[i] = longest common prefix between suffix[i], suffix[i-1] and lcp[0] = 0

void ManberMyers()
{
    // radix sort on the first character
    int hash[257];
    for (int i=0; i<=256; ++i)
    {
        hash[i] = 0;
    }
    for (len=0; str[len] != '\0'; ++len)
    {
        hash[str[len]+1]++;
    }
    for (int i = 1; i <= 256; i++)
    {
        hash[i] += hash[i-1];
    }
    for (int i = 0; i < len; i++)
    {
        suffix[hash[str[i]]] = i;
        hash[str[i]]++;
    }
    
    // initialize BH[] and B2H[]
    BH[0] = true;
    B2H[0] = false;
    for (int i = 1; i < len; i++)
    {
        BH[i] = (str[suffix[i]] != str[suffix[i-1]]);
        B2H[i] = false;
    }

    for (int h = 1; h < len; h <<= 1)
    {
        // reset inverse[] and count[]
        int buckets = 0;
        for (int i = 0,j; i < len; i = j)
        {
            j = i+1;
            while (j < len && !BH[j])
            {
                j++;
            }
            next[i] = j;
            buckets++;
        }
        if (buckets == len)
        {
            break;
        }
        for (int i = 0; i < len; i = next[i])
        {
            count[i] = 0;
            for (int j = i; j < next[i]; j++)
            {
                inverse[suffix[j]] = i;
            }
        }

        // update inverse[] for 2h-bucket
        count[inverse[len-h]]++;
        B2H[inverse[len-h]] = true;
        for (int i = 0; i < len; i = next[i])
        {
            for (int j=i; j<next[i]; ++j)
            {
                int idx = suffix[j] - h;
                if (idx >= 0)
                {
                    count[inverse[idx]]++;
                    inverse[idx] += count[inverse[idx]]-1;
                    B2H[inverse[idx]] = true;
                }
            }
            for (int j=i; j<next[i]; ++j)
            {
                int idx = suffix[j] - h;
                if (idx >= 0)
                {
                    if (B2H[inverse[idx]])
                    {
                        for (int k = inverse[idx]+1; B2H[k] && !BH[k]; k++)
                        {
                            B2H[k] = false;
                        }
                    }
                }
            }
        }

        // update BH[] and suffix[]
        for (int i = 0; i < len; i++)
        {
            BH[i] = BH[i] || B2H[i];
            suffix[inverse[i]] = i;
        }
    }

    for (int i = 0; i < len; i++)
    {
        inverse[suffix[i]] = i;
    }

}

void LCP()
{
    lcp[0] = 0;
    int h = 0;
    for (int i = 0; i < len; i++)
    {
        if (inverse[i] > 0)
        {
            int j = suffix[inverse[i]-1];
            while (i+h < len && j+h < len && str[i+h] == str[j+h])
            {
                h++;
            }
            lcp[inverse[i]] = h;
            if (h > 0)
            {
                h--;
            }
        }
    }
}

int main()
{
    scanf("%s",str);
    ManberMyers();
    for (int i = 0; i < len; i++)
    {
        printf("%d\n",suffix[i]);
    }
    return 0;
}
