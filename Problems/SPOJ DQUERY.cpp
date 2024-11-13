#include<bits/stdc++.h>
using namespace std;
int N, Q, A[30005], ans[200005], F[1000005], sz=200;
vector<pair<int, pair<int, int>>> B[200];

bool compare(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b){
	return a.second.second<b.second.second;
}

int bucket(int pos){ return pos/sz+((pos%sz)>0); }

int first(int buck){ return (buck-1)*sz+1; }

int last(int buck){ return min(first(buck+1)-1, N); }

int brute(int l, int r){
	if(l>r) return 0;
	int cnt=0;
	for(int i=l;i<=r;i++){
		if(!F[A[i]]) cnt++;
		F[A[i]]++;
	}
	for(int i=l;i<=r;i++) F[A[i]]--;
	return cnt;
}

void query(int buck){
	if(B[buck].size()==0) return;
	for(int cnt=0, j=0, i=first(buck+1);i<=N;i++){
		if(!F[A[i]]) cnt++;
 		F[A[i]]++;
		do{
			int q=B[buck][j].first, l=B[buck][j].second.first, r=B[buck][j].second.second;	
			if(i==r){ 
				ans[q]=cnt+brute(l, last(buck));
				j++;
			}
			if(j==B[buck].size()) return;
		}while(i==B[buck][j].second.second);
	}
}

int main(){
	scanf("%d", &N);
	for(int i=1;i<=N;i++)
		scanf("%d", &A[i]);
	scanf("%d", &Q);
	for(int l, r, i=1;i<=Q;i++){
		scanf("%d %d", &l, &r);
		if(bucket(l)==bucket(r)) ans[i]=brute(l, r);
		else B[bucket(l)].push_back({i, {l, r}});
	}
	for(int i=1;i<=bucket(N);i++){
		sort(B[i].begin(), B[i].end(), compare);
		query(i);
		memset(F, 0, sizeof(F));
	}
	for(int i=1;i<=Q;i++)
		printf("%d\n", ans[i]);
	return 0;
}
