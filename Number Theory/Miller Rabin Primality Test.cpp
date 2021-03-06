#include<stdio.h>
#define uint64 unsigned long long

const uint64 pow9 = 1000000000ull;

// Sufficient bases to test primality deterministically upto 10^18
uint64 prime_basis[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

// Needed to prevent overflow during modular multiplication of two 64 bit integers
uint64 mult64(uint64 a, uint64 b, uint64 mod)
{
    uint64 a_high = a/pow9;
    uint64 a_low = a%pow9;
    uint64 b_high = b/pow9;
    uint64 b_low = b%pow9;
    
    uint64 ans = (a_high*b_high)%mod;
    
    for(int i=0; i<9; ++i) ans = (ans*10)%mod;
    
    ans = (ans + a_high*b_low + a_low*b_high)%mod;
    
    for(int i=0; i<9; ++i) ans = (ans*10)%mod;
    
    ans = (ans + a_low*b_low)%mod;
    
    return ans;
}

// Modular exponentiation by repeated squaring
uint64 mod_exp(uint64 a, uint64 x, uint64 mod)
{
    uint64 ans = 1;
    uint64 sqr = a;
    while(x)
    {
        if(x&1) ans = mult64(ans,sqr,mod);
        sqr = mult64(sqr,sqr,mod);
        x >>= 1;
    }
    return ans;
}

// Checks if a is a witness to the compositeness of n
bool witness(uint64 a, uint64 n)
{
    uint64 mod = n;
    n--;

    int count = 0;
    while(!(n&1))
    {
        count++;
        n >>= 1;
    }
    
    uint64 prev = mod_exp(a,n,mod);
    uint64 curr;
    
    for(int i=0; i<count; ++i)
    {
        curr = mult64(prev,prev,mod);
        if(curr == 1 && prev != 1 && prev != (mod-1)) return true;
        prev = curr;
    }
    
    if(curr != 1) return true;
    
    return false;
}

bool miller_rabin(uint64 n)
{
    for(int i=0; i<9; ++i)
    {
        if(prime_basis[i] < n)
        {
            if(witness(prime_basis[i],n)) return false;
        }
        else return true;
    }
    return true;
}

int main()
{
    printf("%d\n",miller_rabin(999999999999999989));
    return 0;
}
