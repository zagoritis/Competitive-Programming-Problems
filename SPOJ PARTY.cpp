#include<bits/stdc++.h>
using namespace std;
int B, N, C[105], F[105], dp[105][105];

int main(){
    while(1){
        scanf("%d %d", &B, &N);
        if(B==0 && N==0) break;
        for(int i=1;i<=N;i++)
            scanf("%d %d", &C[i], &F[i]);
        for(int i=1;i<=N;i++){
            for(int j=B;j>=0;j--){
                if(C[i]<=j)
                    dp[i][j]=max(dp[i-1][j], dp[i-1][j-C[i]]+F[i]);
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        int totalCost=0, totalFun=dp[N][B];
        for(int i=0;i<=B;i++){
            if(dp[N][i]==totalFun){
                totalCost=i;
                break;
            }
        }
        printf("%d %d\n", totalCost, totalFun);
    }
    return 0;
}
