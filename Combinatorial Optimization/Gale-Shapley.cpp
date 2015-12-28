#include<stdio.h>

int main()
{
    //freopen("preferences.in","r",stdin);

    int n;
    scanf("%d",&n);
    
    int** men = new int*[n];
    int** women = new int*[n];
    
    for(int i=0; i<n; ++i)
    {
        men[i] = new int[n];
        women[i] = new int[n];
    }

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            scanf("%d",&men[i][j]);
            men[i][j]--;
        }
    }
    
    int temp;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            scanf("%d",&temp);
            temp--;
            women[i][temp] = j;
        }
    }
    
    int* preference = new int[n];
    for(int i=0; i<n; ++i) preference[i] = 0;
    
    int* married_w = new int[n];
    int* married_m = new int[n];
    for(int i=0; i<n; ++i) married_w[i] = -1;
    
    int* freeing = new int[n];
    for(int i=0; i<n; ++i) freeing[i] = i;
    
    int counter = n-1;
    int suitor,partner,woman;
    while(counter >= 0)
    {
        suitor = freeing[counter];
        woman = men[suitor][preference[suitor]];
        partner = married_w[woman];
        if(partner == -1)
        {
            married_w[woman] = suitor;
            married_m[suitor] = woman;
            counter--;
        }
        else
        {
            if(women[woman][suitor] < women[woman][partner])
            {
                married_w[woman] = suitor;
                married_m[suitor] = woman;
                freeing[counter] = partner;                
            }
        }
        preference[suitor]++;
    }
    
    for(int i=0; i<n; ++i) printf("%d %d\n",i+1,married_m[i]+1);
    
    for(int i=0; i<n; ++i) delete[] men[i],women[i];
    delete[] men,women,married_m,married_w,preference,freeing;
    
    return 0;
}
