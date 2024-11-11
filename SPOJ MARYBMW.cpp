#include<bits/stdc++.h>
using namespace std;
int T, N, M, rnk[50005], p[50005];
pair<long long, pair<int, int>> edges[100005];

void init(){ for(int i=1;i<=N;i++) p[i]=i, rnk[i]=0; }
bool compare(pair<long long, pair<int, int>> a, pair<long long, pair<int, int>> b){ return a>b; }
int findSet(int i){ return p[i]==i ? i : p[i]=findSet(p[i]); }
bool isSameSet(int i, int j){ return findSet(i)==findSet(j); }
void unionSet(int i, int j){
	int x=findSet(i), y=findSet(j);
	if(rnk[x]>rnk[y]) p[y]=x;
	else{
		p[x]=y;
		if(rnk[x]==rnk[y]) rnk[y]++;
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		int flag=0;
		long long ans;
		scanf("%d %d", &N, &M);
		for(int a, b, i=0;i<M;i++){
			long long w;
			scanf("%d %d %lld", &a, &b, &w);
			edges[i]={w, {a, b}};
		}
		sort(edges, edges+M, compare);
		init();
		for(int i=0;i<M;i++){
			long long w=edges[i].first;
			int a=edges[i].second.first, b=edges[i].second.second;
			ans=w;
			if(!isSameSet(a, b)){
				unionSet(a, b);
				if(isSameSet(1, N)){
					flag=1;
					break;
				}
			}
		}
		flag ? printf("%lld\n", ans) : printf("-1\n");
	}
	return 0;
}
