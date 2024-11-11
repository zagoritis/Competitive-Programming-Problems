#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
typedef pair<int, int> pii;
int N, M, C[MAXN], bbegin[MAXN], eend[MAXN], arr[MAXN], F[MAXN], f[MAXN], ans[MAXN], b[320], ttime, sz=320;
vector<pair<pii, pii>> B[320];
vector<int> A[MAXN];
bool visited[MAXN];
 
bool compare(pair<pii, pii> a, pair<pii, pii> b){
	return a.second.second<b.second.second;
}
 
int bucket(int pos){ return pos/sz+((pos%sz)>0); }
 
int first(int buck){ return (buck-1)*sz+1; }
 
int last(int buck){ return min(first(buck+1)-1, N); }
 
int brute_b(int p, int l, int r){
	if(l>r) return 0;
	int sum=0;
	for(int i=l;i<=r;i++){
		if(p) sum+=b[i];
		else sum+=f[i];
	}
	return sum;
}
 
int query_b(int l, int r){
	if(bucket(l)==bucket(r)) return brute_b(0, l, r);
	return brute_b(0, l, last(bucket(l)))+brute_b(1, bucket(l)+1, bucket(r)-1)+brute_b(0, first(bucket(r)), r);
}
 
int brute_B(int l, int r, int k){
	if(l>r) return 0;
	for(int i=l;i<=r;i++){
		f[F[arr[i]]]--;
		b[bucket(F[arr[i]])]--;
		F[arr[i]]++;
		f[F[arr[i]]]++;
		b[bucket(F[arr[i]])]++;
	}
	int ret=query_b(k, N);
	for(int i=l;i<=r;i++){
		f[F[arr[i]]]--;
		b[bucket(F[arr[i]])]--;
		F[arr[i]]--;
		f[F[arr[i]]]++;
		b[bucket(F[arr[i]])]++;
	}
	return ret;
}
 
void query_B(int buck){
	if(!B[buck].size()) return;
	for(int j=0, i=first(buck+1);i<=N;i++){
		f[F[arr[i]]]--;
		b[bucket(F[arr[i]])]--;
		F[arr[i]]++;
		f[F[arr[i]]]++;
		b[bucket(F[arr[i]])]++;
		do{
			int q=B[buck][j].first.first,
				k=B[buck][j].first.second,
				l=B[buck][j].second.first, 
				r=B[buck][j].second.second;	
			if(i==r){ 
				ans[q]=brute_B(l, last(buck), k);
				j++;
			}
			if(j==B[buck].size()) return;
		}while(i==B[buck][j].second.second);
	}
}
 
void dfs(int a){
	if(visited[a]) return;
	visited[a]=true;
	ttime++;
	bbegin[a]=ttime;
	arr[bbegin[a]]=C[a];
	for(auto b : A[a]) dfs(b);
	eend[a]=ttime;
}
 
int main(){
	scanf("%d %d", &N, &M);
	for(int i=1;i<=N;i++)
		scanf("%d", &C[i]);
	for(int a, b, i=1;i<N;i++){
		scanf("%d %d", &a, &b);
		A[a].push_back(b);
		A[b].push_back(a);
	}
	dfs(1);
	for(int v, k, i=1;i<=M;i++){
		scanf("%d %d", &v, &k);
		int l=bbegin[v], r=eend[v];
		if(bucket(l)==bucket(r)) ans[i]=brute_B(l, r, k);
		else B[bucket(l)].push_back({{i, k}, {l, r}});
	}
	for(int i=1;i<=bucket(N);i++){
		sort(B[i].begin(), B[i].end(), compare);
		query_B(i);
		memset(F, 0, sizeof(F));
		memset(f, 0, sizeof(f));
		memset(b, 0, sizeof(b));
	}
	for(int i=1;i<=M;i++)
		printf("%d\n", ans[i]);
	return 0;	
}
