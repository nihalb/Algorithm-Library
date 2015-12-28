#include<stdio.h>
#include<vector>

using namespace std;

#define int64 long long

void extended_euclidean(int64 a, int64 b, int64& x, int64& y)
{
    if(a%b == 0)
    {
        x=0;
        y=1;
        return;
    }
    extended_euclidean(b,a%b,x,y);
    int64 temp = x;
    x = y;
    y = temp - y*(a/b);
}

int64 inverse(int64 a, int64 mod)
{
    int64 x,y;
    extended_euclidean(mod, a, x, y);
    if(y < 0) y += mod;
    return y;
}

/*
    x = a1 (mod n1)
    x = a2 (mod n2)
    where n1, n2 are co-prime
*/
int64 chinese_remainder_theorem(int64 a1, int64 n1, int64 a2, int64 n2)
{
    return (a1 * n2 * inverse(n2, n1) + a2 * n1 * inverse(n1, n2)) % (n1 * n2);
}

/*
    x = a1 (mod n1)
    .
    .
    x = ai (mod ni)
    .
    .
    where n1, ..., ni, ... are co-prime
*/
int64 chinese_remainder_theorem(vector<int64> a, vector<int64> n)
{
    int64 x = a[0];
    int64 mod = n[0];
    for(int i=1; i<a.size(); ++i)
    {
        x = chinese_remainder_theorem(x, mod, a[i], n[i]);
        mod *= n[i];
    }
    return x;
}

int main()
{
    /*
    x = 2 (mod 3)
    x = 3 (mod 4)
    x = 1 (mod 5)
    */
    vector<int64> a;
    a.push_back(2); a.push_back(3); a.push_back(1);
    vector<int64> n;
    n.push_back(3); n.push_back(4); n.push_back(5);
    printf("%lld\n", chinese_remainder_theorem(a, n));
    return 0;
}
