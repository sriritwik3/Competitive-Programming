Refer to this for gilbert order - [An alternative sorting order for Mo's algorithm](https://codeforces.com/blog/entry/61203).  
Refer to this for more on Mo's algorithm - [cp-algorithms](https://cp-algorithms.com/data_structures/sqrt_decomposition.html).  
Written below is the solution to the problem - [D. Powerful array](https://codeforces.com/problemset/problem/86/D).  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define all(v) (v).begin(), (v).end()
#define int long long
#define pl pair<ll,ll> 
const int maxn = 200005;
const int maxel = 1000005;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct Query{
	int l, r, idx;
	int64_t ord;
 
	inline void calcOrder() {
		ord = gilbertOrder(l, r, 21, 0);
	}
};

inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

Query qry[maxn];
int freq[maxel];
int a[maxn];
int ans[maxn];
int store = 0;

void add(int i){
    store -= freq[i]*freq[i]*i;
    freq[i]++;
    store += freq[i]*freq[i]*i;
}

void removee(int i){
    store -= freq[i]*freq[i]*i;
    freq[i]--;
    store += freq[i]*freq[i]*i;
}

signed main()
{
    fastio;
    int n,t;
    cin >> n >> t;
    for(int i=0;i<n;i++) cin >> a[i];
    memset(freq,0,sizeof(freq));
    for(int i=0;i<t;i++){
        int l,r;
        cin >> l >> r;
        --l; --r;
        qry[i].l = l;
        qry[i].r = r;
        qry[i].idx = i;
        qry[i].calcOrder();
    }
    sort(qry,qry+t);
    int cl = qry[0].l, cr = qry[0].l-1;
    for(int i=0;i<t;i++){
        while( cr < qry[i].r ) add(a[++cr]);
        while( cr > qry[i].r ) removee(a[cr--]);
        while( cl < qry[i].l ) removee(a[cl++]);
        while( cl > qry[i].l ) add(a[--cl]);
        ans[qry[i].idx] = store; 
    }
    for(int i=0;i<t;i++) cout << ans[i] << '\n';
    return 0;
}

```
