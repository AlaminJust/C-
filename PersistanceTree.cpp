#include<bits/stdc++.h>

using namespace std;

const int maxn = 1e6;
int RM[maxn];

struct node{
    int cnt;
    node* left , *right;
    node(){
        cnt = 0; left = NULL; right = NULL;
    }
    node(node* _left , node* _right , int _cnt){
        left = _left ; right = _right; cnt = _cnt;
    }
};

void build(node* root , int l , int r){
    if(l == r){
        root->cnt = 0;
        return;
    }
    int mid = (l + r)/2;
    root->left = new node(NULL,NULL,0);
    root->right = new node(NULL,NULL,0);
    build(root->left, l , mid);
    build(root->right , mid + 1 , r);
    root->cnt = root->left->cnt + root->right->cnt;
}

void upgrade(node* prev , node* cur , int l , int r , int idx , int value){
    if (idx > r or idx < l or l > r)
        return;
    if(l == r){
        cur->cnt = value;
        return;
    }
    int mid = (l + r)/2;
    if(idx <= mid){
        cur->right = prev->right;
        cur->left = new node(NULL,NULL,0);
        upgrade(prev->left,cur->left,l,mid,idx,value);
    }
    else{
        cur->left = prev->left;
        cur->right = new node(NULL,NULL,0);
        upgrade(prev->right,cur->right,mid+1,r,idx,value);
    }
    cur->cnt = cur->left->cnt + cur->right->cnt;
}

int query(node* root1 , node* root2 , int l , int r, int k){

    if(l == r){
        return l;
    }
    int diff = (root2->left->cnt - root1->left->cnt);
    int mid = (l + r)/2;
    if(diff >= k){
        return query(root1->left,root2->left,l,mid,k);
    }
    else{
        return query(root1->right , root2->right , mid+1,r,k-diff);
    }
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n , m , i ,x , y , z;
    cin >> n >> m;
    vector < int > A(n+1) , v;
    vector < int > B(n+1);
    node* roots[n+1];
    A[0] = 0;
    for(int i = 1; i<=n; i++){
        cin >> A[i];
        v.push_back(A[i]);
    }
    sort(v.begin(),v.end());
    for(int i = 1; i<=n; i++){
        B[i] = lower_bound(v.begin(),v.end(),A[i])-v.begin();
        RM[B[i]] = A[i];
    }
    node *root = new node(NULL,NULL,0);
    build(root,0,n);
    roots[0]=root;
    for(int i = 1; i<=n; i++){
        roots[i] = new node(NULL,NULL,0);
        upgrade(roots[i-1],roots[i],0,n,B[i],1);
    }
    for(int i = 1; i<=m; i++){
        cin >> x >> y >> z;
        cout << RM[query(roots[x-1],roots[y],0,n,z)] << endl;
    }
    return 0;
}

