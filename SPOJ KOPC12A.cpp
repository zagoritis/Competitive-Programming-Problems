#include <bits/stdc++.h>
using namespace std;
int T, N, c[10005], h[10005];

long long cost(int height){
    long long res=0;
    for(int i=0;i<N;i++)
        res+=c[i]*abs(height-h[i]);
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        for(int i=0;i<N;i++)
            scanf("%d", &h[i]);
        for(int i=0;i<N;i++)
            scanf("%d", &c[i]);
        int l=0, r=10005;
        while(r-l+1 > 3){
            int m1 = l + (r-l)/3;
            int m2 = r - (r-l)/3;
            if(cost(m1) > cost(m2)) l = m1;
            else r = m2;
        }
        long long ans=1e18;
        for(int i=l;i<=r;i++)
            ans=min(ans, cost(i));
        printf("%lld\n", ans);
        memset(c, 0, sizeof(c));
        memset(h, 0, sizeof(h));
    }
    return 0;
}
