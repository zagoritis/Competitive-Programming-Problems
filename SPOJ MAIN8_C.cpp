#include <bits/stdc++.h>
using namespace std;
long int T, N, K, candies[50005], maximum;

bool check(long int x){
    int counter=0;
    for(long int i=0;i<N || counter==K;i++)
        counter+=candies[i]/x;
    return counter>=K;
}

int main() {
    scanf("%ld", &T);
    for(int t=0;t<T;t++){
        scanf("%ld %ld", &N, &K);
        for(long int i=0;i<N;i++) {
            scanf("%ld", &candies[i]);
            maximum=max(maximum, candies[i]);
        }
        long int k=0;
        for(long int b=maximum;b>0;b/=2)
            while(check(k+b)) k+=b;
        printf("%ld\n", k);
    }
    return 0;
}
