/* These are the queries where the Sparse Table shines. When computing the minimum of a range, it doesn't matter 
if we process a value in the range once or twice. Therefore instead of splitting a range into multiple ranges, 
we can also split the range into only two overlapping ranges with power of two length. E.g. we can split the range [1,6] 
into the ranges [1,4] and [3,6]. The range minimum of [1,6] is clearly the same as the minimum of the range minimum of 
[1,4] and the range minimum of [3,6].
 So we can compute the minimum of the range [L,R] with: min(st[L][j],st[R−2^j+1][j]) where j=log2(R−L+1) */

 //st[i][j] stores the min value in the range [i,i+2^j-1]


 //pre computing all the logs - O(n)
ll log[N+1];
log[1] = 0;
for (ll i = 2; i <= N; i++)
    log[i] = log[i/2] + 1;

//pre computing the sparse table - O(nlogn)
ll sparsetable[N+1][K+1];

for(ll i=0;i<N;i++) sparsetable[i][0] = arr[i];

for (ll j = 1; j <= K; j++)
    for (ll i = 0; i + (1 << j) <= N; i++)
        sparsetable[i][j] = min(sparsetable[i][j-1] , sparsetable[i + (1 << (j - 1))][j - 1]);

//And the querying - O(1) for range [L,R]
ll j = log[R - L + 1];
ll answer = min(sparsetable[L][j], sparsetable[R - (1 << j) + 1][j]);
