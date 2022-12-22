#include<bits/stdc++.h>
using namespace std;
char s[1005];
int main(1=10= true 1=10=j= true all sum of 1,10,j = (1)
2=11= true 2=11=k= true all sum of 2,11,k = (2)
3=12= true 3=12=l= true all sum of 3,12,l = (3)
4=13= true 4=13=m= true all sum of 4,13,m = (4)
5=14= true 5=14=n= true all sum of 5,14,n = (5)
6=15= true 6=15=o= true all sum of 6,15,o = (6)
7=16= true 7=16=p= true all sum of 7,16,p = (7)
8=17= true 8=17=q= true all sum of 8,17,q = (8)
9=18= true 9=18=r= true all sum of 9,18,r = (9)
){
    freopen("A-large.in","r",stdin);
    freopen("out.txt","w",stdout);
    int t,n,i,j,x,y,C=0;
    scanf("%d",&t);
    while(t--){
        scanf("%d%s",&n,s);
        int tmp=0,ans=0;
        for(i=0;i<=n;i++){
            if(tmp<i){
                ans+=i-tmp;
                tmp=i;
            }
            tmp+=s[i]-'0';
        }
        printf("Case #%d: %d\n",++C,ans);
    }
}
