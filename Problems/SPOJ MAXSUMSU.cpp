#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000005
int T, N, A[MAXN];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		for(int i=1;i<=N;i++)
			scanf("%d", &A[i]);
		int sum=0, best=0;
		for(int i=1;i<=N;i++){
			sum=max(A[i], sum+A[i]);
			best=max(best, sum);
		}
		printf("%d\n", best);
	}
	return 0;
}
