#include<bits/stdc++.h>
using namespace std;
#define BASE 526
#define MAXN 100005
int N;
char P[MAXN];
unsigned long long hash1, A1[MAXN], A2[MAXN];

int main(){
	scanf("%d %s", &N, P+1);
	for(int i=N;i>0;i--){
		hash1*=BASE;
		hash1+=P[i];
		A1[i]=hash1;
	}
	unsigned long long x=0, b=1;
	for(int i=N;i>0;i--){
		x+=P[i]*b;
		b*=BASE;
		A2[i]=x;
	}
	for(int i=1;i<=N;i++){
		if(A1[i]==A2[i]){
			printf("%d", i-1);
			break;
		}
	}
	return 0;
}
