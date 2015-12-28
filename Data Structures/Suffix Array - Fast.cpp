#include<stdio.h>
#include<algorithm>

using namespace std;

const int max_n = 100000+5;
const int infinity = 1000000000;

char str[max_n];                 // contains the string
int len;                         // denotes the length of the string
int suffix[max_n];               // suffix[i] = index of the suffix at rank i
int inverse[max_n];              // inverse[i] = rank of the i-th suffix
bool BH[max_n];                  // BH[i] = true only if i is the first suffix in its h-bucket
int next[max_n];                 // next[i] = the first index to occur after the i's bucket
int counter[max_n];
bool B2H[max_n];

int lcp[max_n];                  // lcp[i] = longest common prefix between suffix[i], suffix[i-1] and lcp[0] = 0

void manber_myers()
{
    // radix sort on the first character
    int hash[257];
    for (int i=0; i<=256; ++i) hash[i] = 0;
    for (len=0; str[len] != '\0'; ++len) hash[str[len]+1]++;
    for (int i = 1; i <= 256; i++) hash[i] += hash[i-1];
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
        // reset inverse[] and counter[]
        int buckets = 0;
        for (int i = 0,j; i < len; i = j)
        {
            j = i+1;
            while (j < len && !BH[j]) j++;
            next[i] = j;
            buckets++;
        }
        if (buckets == len) break;
        for (int i = 0; i < len; i = next[i])
        {
            counter[i] = 0;
            for (int j = i; j < next[i]; j++) inverse[suffix[j]] = i;
        }

        // update inverse[] for 2h-bucket
        counter[inverse[len-h]]++;
        B2H[inverse[len-h]] = true;
        for (int i = 0; i < len; i = next[i])
        {
            for (int j=i; j<next[i]; ++j)
            {
                int idx = suffix[j] - h;
                if (idx >= 0)
                {
                    counter[inverse[idx]]++;
                    inverse[idx] += counter[inverse[idx]]-1;
                    B2H[inverse[idx]] = true;
                }
            }
            for (int j=i; j<next[i]; ++j)
            {
                int idx = suffix[j] - h;
                if (idx >= 0) if (B2H[inverse[idx]]) for (int k = inverse[idx]+1; B2H[k] && !BH[k]; k++) B2H[k] = false;
            }
        }

        // update BH[] and suffix[]
        for (int i = 0; i < len; i++)
        {
            BH[i] = BH[i] || B2H[i];
            suffix[inverse[i]] = i;
        }
    }

    for (int i = 0; i < len; i++) inverse[suffix[i]] = i;
}

void build_lcp()
{
    lcp[0] = 0;
    int h = 0;
    for (int i = 0; i < len; i++)
    {
        if (inverse[i] > 0)
        {
            int j = suffix[inverse[i]-1];
            while (i+h < len && j+h < len && str[i+h] == str[j+h]) h++;
            lcp[inverse[i]] = h;
            if (h > 0) h--;
        }
    }
}

int* segment;

void initialize(int index, int A[], int a, int b)
{
    if(a > b) return;
    if(a == b)
    {
        segment[index] = A[a];
        return;
    }
    int mid = a + (b-a)/2;
    initialize(2*index,A,a,mid);
    initialize(2*index+1,A,mid+1,b);
    segment[index] = min(segment[2*index], segment[2*index+1]);
}

void build_tree(int A[], int size)
{
    int c = 1;
    int temp = size;
    while(temp)
    {
        temp >>= 1;
        c++;
    }
    c = 1<<c;
    segment = new int[c];
    initialize(1,A,0,size-1);
}

int query(int index, int left, int right, int a, int b)
{
    if(left > right || right < a || left > b) return infinity;
    if(a <= left && b >= right) return segment[index];
    int mid = left + (right-left)/2;
    return min(query(2*index,left,mid,a,b), query(2*index+1,mid+1,right,a,b));
}

int query_tree(int i, int j, int size)
{
    return query(1,0,size-1,i,j);
}

void clear_tree()
{
    delete[] segment;
}

int main()
{
    scanf("%s",str);
    manber_myers();
    for (int i = 0; i < len; i++) printf("%d\n",suffix[i]);
    
    build_lcp();
    build_tree(lcp, len);
    clear_tree();
    
    return 0;
}
