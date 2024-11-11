#include<bits/stdc++.h>
using namespace std;
#define MAXN 200005
int N, M, rnk[MAXN], D[MAXN], par[MAXN][35], maxE[MAXN][35];
pair<int, pair<int, int>> edges[MAXN], Sedges[MAXN];
vector<pair<int, int>> A[MAXN];
bool visited[MAXN];

int findSet(int i){ return par[i][0]==i ? i : par[i][0]=findSet(par[i][0]); }

bool isSameSet(int i, int j){ return findSet(i)==findSet(j); }

void unionSet(int i, int j){
	int x=findSet(i), y=findSet(j);
	if(rnk[x]>rnk[y]) par[y][0]=x;
	else{
		par[x][0]=y;
		if(rnk[x]==rnk[y]) rnk[y]++;
	}
}

void preCompute(){
	for(int i=1;i<=30;i++){
		for(int j=1;j<=N;j++){
			par[j][i]=par[par[j][i-1]][i-1];
			maxE[j][i]=max(maxE[j][i-1], maxE[par[j][i-1]][i-1]);
		}
	}
}

long long lca(int u, int v){
	if(D[u]<D[v]) swap(u, v);
	int numToClimb=D[u]-D[v], maxEdge=0;
	for(int i=30;i>=0;i--){
		if((1<<i)<=numToClimb){
			numToClimb-=(1<<i);
			maxEdge=max(maxEdge, maxE[u][i]);
			u=par[u][i];
		}
	} 
	for(int i=30;i>=0;i--){
		if(par[u][i]==par[v][i]) continue;
		maxEdge=max(maxEdge, max(maxE[u][i], maxE[v][i]));
		u=par[u][i], v=par[v][i];
	}
	if(u!=v) maxEdge=max(maxEdge, max(maxE[u][0], maxE[v][0]));
	return maxEdge;
}

void dfs(int u, int d, int parent, int parentDist){
	if(visited[u]) return;
	visited[u]=true;
	par[u][0]=parent;
	maxE[u][0]=parentDist;
	D[u]=d;
	for(auto v : A[u]) 
		dfs(v.first, d+1, u, v.second);
}

int main(){
	scanf("%d %d", &N, &M);
	for(int u, v, w, i=1;i<=M;i++){
		scanf("%d %d %d", &u, &v, &w);
		edges[i]=Sedges[i]={w, {u, v}};
	}
	sort(Sedges+1, Sedges+M+1);
	long long MSTweight=0;
	for(int i=1;i<=N;i++) par[i][0]=i;
	for(int i=1;i<=M;i++){
		int w=Sedges[i].first, u=Sedges[i].second.first, v=Sedges[i].second.second;
		if(!isSameSet(u, v)){
			unionSet(u, v);
			MSTweight+=w;
			A[u].push_back({v, w});
			A[v].push_back({u, w});
		}
	}
	dfs(1, 1, 0, 0);
	preCompute();
	for(int i=1;i<=M;i++){
		int w=edges[i].first, u=edges[i].second.first, v=edges[i].second.second;
		printf("%lld\n", MSTweight-lca(u, v)+w);
	}
	return 0;
}
