#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 10005
int N, M, K, S, T, dist[MAXN], ans;
vector<pair<int, int>> A[MAXN];
bool processed[MAXN];

void dijkstra(int x){
	priority_queue<pair<int, int>> q;
	for(int i=1;i<=N;i++)
		dist[i]=INF, processed[i]=false;
	dist[x]=0;
	q.push({0, x});
	while(!q.empty()){
		int v=q.top().second; q.pop();
		if(processed[T]) return;
		if(processed[v]) continue;
		processed[v]=true;
		for(auto u : A[v]){
			int b=u.first, w=u.second;
			if(dist[b]>dist[v]+w){
				dist[b]=dist[v]+w;
				q.push({-dist[b], b});
			}
		}
	}
}

int main(){
	scanf("%d %d %d %d %d", &N, &M, &K, &S, &T);
	for(int a, b, w, i=1;i<=M;i++){
		scanf("%d %d %d", &a, &b, &w);
		A[a].push_back({b, w});
	}
	dijkstra(S);
	ans=dist[T];
	for(int a, b, w, i=1;i<=K;i++){
		scanf("%d %d %d", &a, &b, &w);
		A[a].push_back({b, w});
		dijkstra(S);
		ans=min(ans, dist[T]);
		A[a].pop_back();
	}
	printf("%d\n", ans);
	return 0;
}
