#include<stdio.h>

int main()
{
    freopen("preferences.in","r",stdin);

    int n;
    scanf("%d",&n);
    
    int** Men = new int*[n];
    int** Women = new int*[n];
    
    for(int i=0; i<n; ++i)
    {
        Men[i] = new int[n];
        Women[i] = new int[n];
    }

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            scanf("%d",&Men[i][j]);
            Men[i][j]--;
        }
    }
    
    int temp;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            scanf("%d",&temp);
            temp--;
            Women[i][temp] = j;
        }
    }
    
    int* Preference = new int[n];
    for(int i=0; i<n; ++i)
    {
        Preference[i] = 0;
    }
    
    int* MarriedW = new int[n];
    int* MarriedM = new int[n];
    for(int i=0; i<n; ++i)
    {
        MarriedW[i] = -1;
    }
    
    int* Free = new int[n];
    for(int i=0; i<n; ++i)
    {
        Free[i] = i;
    }
    
    int Count = n-1;
    int Suitor,Partner,Woman;
    while(Count >= 0)
    {
        Suitor = Free[Count];
        Woman = Men[Suitor][Preference[Suitor]];
        Partner = MarriedW[Woman];
        if(Partner == -1)
        {
            MarriedW[Woman] = Suitor;
            MarriedM[Suitor] = Woman;
            Count--;
        }
        else
        {
            if(Women[Woman][Suitor] < Women[Woman][Partner])
            {
                MarriedW[Woman] = Suitor;
                MarriedM[Suitor] = Woman;
                Free[Count] = Partner;                
            }
        }
        Preference[Suitor]++;
    }
    
    for(int i=0; i<n; ++i)
    {
        printf("%d %d\n",i+1,MarriedM[i]+1);
    }
    
    for(int i=0; i<n; ++i)
    {
        delete[] Men[i],Women[i];
    }
    delete[] Men,Women,MarriedM,MarriedW,Preference,Free;
    
    return 0;
}
