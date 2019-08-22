/// https://codeforces.com/contest/486/problem/E
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5;
int data[maxn] , n ,Lis[maxn],Lds[maxn];
int a[maxn],b[maxn];
int num , mx = -1;

void LIS(){
   for(int i=0;i<=n+1;i++)a[i]=b[i]=INT_MAX;
   a[0]=INT_MIN;
   num=0;
   for(int i=0;i<n;i++){
       int low=lower_bound(a,a+n+1,data[i])-a;
       a[low]=data[i];
       mx=max(mx,data[i]);
       num=max(num,low);
       Lis[i]=low;
   }
}

 void LDS(){
    b[0]=INT_MIN;
    for(int i=n-1;i>=0;i--){
         int low=lower_bound(b,b+n+1,mx-data[i])-b;
         b[low]=mx-data[i];
         Lds[i]=low;
    }
  }
int main()
{
  scanf("%d",&n);
   for(int i=0;i<n;i++){
        scanf("%d",&data[i]);
   }
   LIS();
   LDS();
//   for(int i = 0; i<n; i++)cout << Lis[i] << " ";
//   cout << endl;
//   for(int i = 0; i<n; i++)cout << Lds[i] << " ";
//   cout << endl;
   int freq[n+10];
   memset(freq,0,sizeof freq);
   int ok[n+10];
   memset(ok,0,sizeof ok);
   for(int i=0;i<n;i++){
      if(Lis[i]+Lds[i]-1==num){
          ok[i]=1;
          freq[Lis[i]]++;
      }
   }
   for(int i=0;i<n;i++){
       if(ok[i]==0)cout<<1;
       else if(freq[Lis[i]]==1)cout<<3;
       else cout<<2;
   }
  return 0;
}

