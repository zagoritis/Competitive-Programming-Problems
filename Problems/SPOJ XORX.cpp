#include<bits/stdc++.h>
#define trianta 30
#define MAXN 200005
using namespace std;
int T, N, X, A[MAXN], prefXor[MAXN], child[MAXN*35][2], newNode;

void add(int x){
	int curr=0, bit=0;
	for(int i=30;i>=0;i--){
		bit=(x&(1<<i))>0;
		if(child[curr][bit]==0){
			newNode++;
			child[curr][bit]=newNode;
		}
		curr=child[curr][bit];
	}
}

int search(int x){
	int curr=0, res=0, bit=0;
	for(int i=30;i>=0;i--){
		bit=(x&(1<<i))>0;
		if(child[curr][bit]){
			if(bit) res|=(1<<i);
			curr=child[curr][bit];
		}
		else if(child[curr][bit^1]){
			if(bit^1) res|=(1<<i);
			curr=child[curr][bit^1];
		}
	}
	return res;
}
 
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d %d", &N, &X);
		for(int i=1;i<=N;i++)
			scanf("%d", &A[i]);
		int ans=0, opt=X^((1<<(trianta+1))-1);
		add(prefXor[0]);
		for(int i=1;i<=N;i++){
			prefXor[i]=A[i]^prefXor[i-1];
			int res=search(prefXor[i]^opt);
			if(ans < (res^X^prefXor[i]))
				ans=res^X^prefXor[i];
			add(prefXor[i]);
		}
		newNode=0;
		memset(child, 0, sizeof(child));
		printf("%d\n", ans^X);
	}
	return 0;
}
