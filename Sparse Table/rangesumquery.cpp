/* We will use a 2-dimensional array for storing the answers to the precomputed queries. 
st[i][j] will store the answer for the range [i,i+2^j−1] of length 2^j. 
The size of the 2-dimensional array will be MAXN × (K+1), where MAXN is the biggest possible array length.
K has to satisfy K≥⌊log2MAXN⌋, because 2⌊log2MAXN⌋ is the biggest power of two range, that we have to support. 
For arrays with reasonable length (≤10^7 elements), K=25 is a good value.*/

/* Because the range [i,i+2^j−1] of length 2^j splits nicely into the ranges [i,i+2^(j−1)−1] and [i+2^(j−1),i+2^j−1],
both of length 2^(j−1), we can generate the table efficiently using dynamic programming:*/

ll sparsetable[MAXN][K+1];

for(ll i=0;i<N;i++) sparsetable[i][0] = arr[i];

for (ll j = 1; j <= K; j++)
    for (ll i = 0; i + (1 << j) <= N; i++)
        sparsetable[i][j] = sparsetable[i][j-1] + sparsetable[i + (1 << (j - 1))][j - 1];

// This pre computation in sparse table takes O(nlogn).

/*To answer the sum query for the range [L,R], we iterate over all powers of two, starting from the biggest one.
As soon as a power of two 2^j is smaller or equal to the length of the range (=R−L+1), 
we process the first the first part of range [L,L+2^j−1], and continue with the remaining range [L+2^j,R].*/

ll sum = 0;
for (ll j = K; j >= 0; j--) {
    if ((1 << j) <= R - L + 1) {
        sum += sparsetable[L][j];
        L += 1 << j;
    }
}

//Time complexity for a Range Sum Query is O(K)=O(logMAXN).