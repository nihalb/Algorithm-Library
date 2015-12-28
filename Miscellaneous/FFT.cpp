#include<stdio.h>
#include<math.h>
#include<complex>
#include<vector>

using namespace std;

typedef complex<double> cd;

int get_size(int n)
{
    if(!(n & (n-1))) return n;
    int t = 0;
    while(n)
    {
        n >>= 1;
        t++;
    }
    return 1 << t;
}

void compute_fft(vector<cd>& a, cd omega)
{
    int N = a.size();
    if(N == 1) return;
    vector<cd> a_even;
    vector<cd> a_odd;
    for(int i=0; i<N; i+=2)
    {
        a_even.push_back(a[i]);
        a_odd.push_back(a[i+1]);
    }
    compute_fft(a_even, omega * omega);
    compute_fft(a_odd, omega * omega);
    cd mult = cd(1,0);
    for(int i=0; i<N/2; ++i)
    {
        a[i] = a_even[i] + mult * a_odd[i];
        a[i + N/2] = a_even[i] - mult * a_odd[i];
        mult *= omega;
    }
}

vector<cd> fft(vector<cd> a)
{
    int N = get_size(a.size());
    a.resize(N);
    compute_fft(a, cd (cos(2 * M_PI / N), sin(2 * M_PI / N)));
    return a;
}

vector<cd> inverse_fft(vector<cd> a)
{
    int N = get_size(a.size());
    a.resize(N);
    compute_fft(a, cd (cos(-2 * M_PI / N), sin(-2 * M_PI / N)));
    for(int i=0; i<N; ++i) a[i] /= N;
    return a;
}

int main()
{
    vector<cd> a;
    a.push_back(cd(1,0));
    a.push_back(cd(2,0));
    a.push_back(cd(3,0));
    a.push_back(cd(4,0));
    vector<cd> A = fft(a);
    for(int i=0; i<4; ++i) printf("%lf %lf\n", A[i].real(), A[i].imag());
    vector<cd> b = inverse_fft(A);
    for(int i=0; i<4; ++i) printf("%lld\n", (long long) (b[i].real() + 0.5));
    return 0;
}
