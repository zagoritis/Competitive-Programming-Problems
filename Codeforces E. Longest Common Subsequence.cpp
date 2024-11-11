#include<bits/stdc++.h>
using namespace std;
#define MAXN 1005
int dp[MAXN][MAXN];
char S1[MAXN], S2[MAXN];
bool compute[MAXN][MAXN];

int solve(int n, int m){
	if(!n || !m) return 0;
	if(compute[n][m]) return dp[n][m];
	compute[n][m]=true;
	if(S1[n-1]==S2[m-1])
		dp[n][m]=solve(n-1, m-1)+1;
	else
		dp[n][m]=max(solve(n-1, m), solve(n, m-1));
	return dp[n][m];
}

int main(){
	while(gets(S1)){
		gets(S2);
		int n=strlen(S1), m=strlen(S2);
		printf("%d\n", solve(n, m));
		memset(compute, 0, sizeof(compute));
	}
	return 0;
}
