#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
int N, Q, W[MAXN], par[MAXN][35], D[MAXN];
long long sum[MAXN];
vector<int> A[MAXN];

void preCompute(){
	for(int i=1;i<=30;i++)
		for(int j=1;j<=N;j++)
			par[j][i]=par[par[j][i-1]][i-1];
}

int KthAncestor(int X, int K){
	for(int i=30;i>=0;i--){
		if((1<<i)<=K){
			K-=(1<<i);
			X=par[X][i];
		}
	}
	return X;
}

int lca(int a, int b){
	if(D[a]<D[b]) swap(a, b);
	int numToClimb=D[a]-D[b];
	for(int i=30;i>=0;i--){
		if((1<<i)<=numToClimb){
			numToClimb-=(1<<i);
			a=par[a][i];
		}
	}
	if(a==b) return a;
	for(int i=30;i>=0;i--){
		if(par[a][i]==par[b][i]) continue;
		a=par[a][i], b=par[b][i];
	}
	return par[a][0]; 
}

long long query(int x, int root){
	if(x==root) return sum[1];
	else if(lca(x, root)!=x) 
		return sum[x];
	else{
		int w=KthAncestor(root, D[root]-D[x]-1);
		return sum[1]-sum[w];
	}
}

void dfs(int a, int d){
	sum[a]=W[a];
	D[a]=d;
	for(auto b : A[a]){
		dfs(b, d+1);
		sum[a]+=sum[b];
	}
}

int main(){
	scanf("%d", &N);
	for(int i=1;i<=N;i++)
		scanf("%d", &W[i]);
	for(int i=2;i<=N;i++){
		scanf("%d", &par[i][0]);
		A[par[i][0]].push_back(i);
	}
	dfs(1, 1);
	preCompute();
	scanf("%d", &Q);
	int root=1;
	for(int x, i=1;i<=Q;i++){
		char option;
		scanf(" %c %d\n", &option, &x);
		if(option=='R') root=x;
		else printf("%lld\n", query(x, root));
	}
	return 0;
}
