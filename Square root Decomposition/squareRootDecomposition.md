Consider the array to be 0-indexed.  
[refer to this](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)
```cpp
ll sum = 0;
ll len = (ll)sqrt(n+.0) + 1
ll b[len];
for(ll i=0;i<len;i++)
    b[i/len] += a[i]
ll l_block = l/len, r_block = r/len;

//for each query

if(l_block == r_block)
    for(ll i=l;i<=r;i++)
        sum += a[i] // a is the original array   
else{
    for (ll i=l, i<=(l_block+1)*len-1; i++)
        sum += a[i];
    for (ll i=l_block+1; i<=r_block-1; i++)
        sum += b[i];
    for (ll i=r_block*len; i<=r; i++)
        sum += a[i];
 }
```
