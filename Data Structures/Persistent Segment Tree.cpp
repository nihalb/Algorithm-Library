#include<stdio.h>
#include<vector>

using namespace std;

struct node
{
    node() : left(NULL), right(NULL), val(0) {}
    node(node* l, node* r, int v) : left(l), right(r), val(v) {}
    node* left;
    node* right;
    int val;
};

// init(A,0,n-1) for 0-indexed arrays
node* init(int A[], int l, int r)
{
    if(l == r) return new node(NULL, NULL, A[l]);
    int m = l+(r-l)/2;
    node* p = new node(init(A,l,m), init(A,m+1,r), 0);
    p->val = (p->left)->val + (p->right)->val;
    return p;
}

// update(A,i,v,0,n-1) for 0-indexed arrays
node* update(node* latest, int i, int v, int l, int r)
{
    if(i < l || i > r) return latest;
    if(l == r && l == i) return new node(NULL, NULL, v);
    int m = l+(r-l)/2;
    node* p = new node(update(latest->left,i,v,l,m), update(latest->right,i,v,m+1,r), 0);
    p->val = (p->left)->val + (p->right)->val;
    return p;
}

// query(A,L,R,0,n-1) for 0-indexed arrays
int query(node* root, int L, int R, int l, int r)
{
    if(R < l || L > r) return 0;
    if(L <= l && R >= r) return root->val;
    int m = l+(r-l)/2;
    return query(root->left,L,R,l,m) + query(root->right,L,R,m+1,r);
}

int main()
{
    int A[] = {0,1,2,3,4};
    vector<node*> versions;
    versions.push_back(init(A,0,4));
    versions.push_back(update(versions.back(),2,5,0,4));
    versions.push_back(update(versions.back(),4,-1,0,4));
    printf("%d\n", query(versions[0],0,4,0,4));
    printf("%d\n", query(versions[0],1,3,0,4));
    printf("%d\n", query(versions[1],1,3,0,4));
    printf("%d\n", query(versions[1],2,4,0,4));
    printf("%d\n", query(versions[2],2,4,0,4));
    return 0;
}
