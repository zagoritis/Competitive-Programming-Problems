#include <bits/stdc++.h>
using namespace std;

int T, N, M;
string destination;
unordered_map<string, int> par;
pair<int,int> moves[12*12+5];

string make_move(int i, const string &v){
	string u = v;
	swap(u[moves[i].first-1], u[moves[i].second-1]);
	return u;
}

int bfs(const string &source){
	queue<string> q;
	unordered_map<string, int> dist;
	unordered_map<string, bool> used;
	q.push(source);
	dist[source] = 0;
	used[source] = true;
	par[source] = -1;
	while(!q.empty()){
		string v=q.front(); q.pop();
		if(v == destination)
			return dist[v];

		for(int i=0; i<M; i++){
			string u = make_move(i, v);
			if(!used[u]){
				used[u] = true;
				dist[u] = dist[v] +1;
				q.push(u);
				par[u] = i;
			}
		}
	}
	return -1;
}

void print_path(string v){
	if(par[v]==-1)
		return;
	
	string u = make_move(par[v], v);
	print_path(u);
	printf("%d\n", par[v]+1);
}

int main(){
	scanf("%d%d", &T, &N);
	for(int i=1; i<=N; i++)
		destination.push_back(i+'0');

	while(T--){
		par.clear();
		scanf("%d", &M);
		string source;
		for(int tmp,i=1; i<=N; i++){
			scanf("%d", &tmp);
			source.push_back(tmp+'0');
		}
		for(int i=0; i<M; i++)
			scanf("%d%d", &moves[i].first, &moves[i].second);

		int moves = bfs(source);
		if(moves == -1)
			printf("IMPOSSIBLE\n");
		else{
			printf("MOVES %d\n", moves);
			print_path(destination);
		}
	}
	return 0;
}
