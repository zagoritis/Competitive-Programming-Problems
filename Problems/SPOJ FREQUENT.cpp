#include <bits/stdc++.h>
using namespace std;
int N, Q ,A[100005];
struct data{
    int maxLeft, left, maxRight, right, max;
}st[400005];

data combine(data l, data r){
    data res={l.maxLeft, l.left, r.maxRight, r.right, max(l.max, r.max)};
    if(l.maxRight==r.maxLeft)
        res.max=max(res.max, l.right+r.left);
    if(l.maxLeft==r.maxLeft)
        res.left+=r.left;
    if(l.maxRight==r.maxRight)
        res.right+=l.right;
    return res;
}

void build(int v=1, int start=1, int end=N){
    if(start==end){
        st[v]={A[start], 1, A[start], 1, 1};
        return;
    }
    int mid=(start+end)/2;
    build(2*v, start, mid);
    build(2*v+1, mid+1, end);
    st[v]=combine(st[2*v], st[2*v+1]);
}

data query(int l, int r, int v=1, int start=1, int end=N){
    if(l==start && r==end)
        return st[v];
    int mid=(start+end)/2;
    if(r<=mid)
        return query(l, r, 2*v, start, mid);
    else if(l>mid)
        return query(l, r, 2*v+1, mid+1, end);
    else
        return combine(query(l, mid, 2*v, start, mid), query(mid+1, r, 2*v+1, mid+1, end));
}

int main() {
    while(1){
        scanf("%d %d", &N, &Q);
        if(!N) break;
        for(int i=1;i<=N;i++)
            scanf("%d", &A[i]);
        build();
        for(int x, y, i=1;i<=Q;i++){
            scanf("%d %d", &x, &y);
            printf("%d\n", query(x, y).max);
        }
    }
    return 0;
}
