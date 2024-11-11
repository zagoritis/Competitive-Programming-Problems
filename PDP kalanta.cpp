#include<bits/stdc++.h>
using namespace std;
int N, arr[2000005], totalSum;

int main(){
    scanf("%d", &N);
    for(int i=1;i<=N;i++){
        scanf("%d", &arr[i]);
        arr[N+i]=arr[i];
        totalSum+=arr[i];
    }
    int left=1, currSum=0, best=1e9;
    for(int right=1;right<=2*N;right++){
        currSum+=arr[right];
        while(currSum>totalSum/2){
            currSum-=arr[left];
            left++;
        }
        best=min(best, abs(totalSum-2*currSum));
        if(!best) break;
    }
    printf("%d\n", best);
    return 0;
}