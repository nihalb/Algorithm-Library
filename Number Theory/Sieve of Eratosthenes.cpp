#include<stdio.h>
#include<vector>

using namespace std;

const int max_n = 100000 + 5;
bool table[max_n];
vector<int> primes;

void sieve()
{
    for(int i=0; i<max_n; ++i) table[i] = true;
    for(int i=2; i*i<max_n; ++i) if(table[i]) for(int j=i*i; j<max_n; j+=i) table[j] = false;
    primes.push_back(2);
    for(int i=3; i<max_n; i+=2) if(table[i]) primes.push_back(i);
}

int main()
{
    sieve();
    for(int i=0; i<10; ++i) printf("%d\n", primes[i]);
    return 0;
}
