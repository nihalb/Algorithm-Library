#include<stdio.h>
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

int main()
{
    int64 mod = 1000000007;
    for(int64 a=1; a<5; ++a) printf("%lld\n", inverse(a,mod));
    return 0;
}
