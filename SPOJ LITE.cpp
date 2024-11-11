#include <bits/stdc++.h>
using namespace std;
int N, M, st[400005], lazy[400005];

void propagate(int v, int start, int end);

void update(int l, int r, int v=1 ,int start=1, int end=N){
    if(l==start && r==end){
        st[v]=(end-start+1)-st[v];
        lazy[v]++;
        return;
    }
    propagate(v, start, end);
    int mid=(start+end)/2;
    if(r<=mid) update(l, r, 2*v, start, mid);
    else if(l>mid) update(l, r, 2*v+1, mid+1, end);
    else{
        update(l ,mid, 2*v, start, mid);
        update(mid+1, r, 2*v+1, mid+1, end);
    }
    st[v]=st[2*v]+st[2*v+1];
}

void propagate(int v, int start, int end){
    if(lazy[v]%2){
        int mid=(start+end)/2;
        update(start, mid, 2*v, start, mid);
        update(mid+1, end, 2*v+1, mid+1, end);
        lazy[v]=0;
    }
}

int query(int l, int r, int v=1, int start=1, int end=N){
    if(l==start && r==end)
        return st[v];
    propagate(v, start, end);
    int mid=(start+end)/2;
    if(r<=mid) return query(l, r, 2*v, start, mid);
    else if(l>mid) return query(l, r, 2*v+1, mid+1, end);
    else return query(l, mid, 2*v, start, mid)+query(mid+1, r, 2*v+1, mid+1, end);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int q, l, r, i=1;i<=M;i++){
        scanf("%d %d %d", &q, &l, &r);
        if(!q) update(l, r);
        else printf("%d\n", query(l, r));
    }
    return 0;
}
