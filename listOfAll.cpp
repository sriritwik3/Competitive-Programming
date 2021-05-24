#include<iostream>
#include<algorithm>
#include<limits.h>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

//*******************......................NUMBER - THEORY....................********************

//divisors in nlogn
void positive_divisors(ll divisors[]){
    for(ll i=1;i<=1000001;i++)
        for(ll j=i;j<=1000001;j+=i)
            ++divisors[j];
}       
//end of divisors


//*****************..........................SEGMENT - TREES.................*********************

// min segment Tree passing as an argument

void buildSegmentTree(ll a[],ll st[],ll si,ll ss, ll se){
    if(ss == se){
        st[si] = a[se];
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildSegmentTree(a,st,2*si,ss,mid);
    buildSegmentTree(a,st,2*si+1,mid+1,se);
    st[si] = min(st[2*si],st[2*si+1]);
}

ll segmentTreeQuery(ll st[],ll si, ll ss, ll se, ll qs,ll qe){
    if(ss > qe || qs > se) return INT_MAX;
    if(qs <= ss && qe >= se) return st[si];
    ll mid = ss + (se-ss)/2;
    return min(segmentTreeQuery(st,2*si,ss,mid,qs,qe),
    segmentTreeQuery(st,2*si+1,mid+1,se,qs,qe));
}

void pointUpdateSegTree(ll a[],ll st[],ll si,ll ss,ll se,ll ui){
    //You have to update in the original array first
    if(ss == se){
        st[si] = a[ss];
        return;
    }
    ll mid = ss + (se-ss)/2;
    if(ui <= mid) pointUpdateSegTree(a, st, 2*si, ss, mid, ui);
    else pointUpdateSegTree(a,st,2*si+1,mid+1,se,ui);
    st[si] = min(st[2*si],st[2*si+1]);
}

//end of min seg tree


//start of lazy propagation for range updates in segment tree


ll lazyPropQuery(ll st[],ll lazy[],ll si, ll ss, ll se, ll qs,ll qe){
    //lazy array must be initialised to 0
    if(lazy[si] != 0 ){
        ll add = lazy[si];
        lazy[si] = 0;
        st[si] += (se-ss+1)*add;
        if(se != ss) lazy[2*si] += add, lazy[2*si+1] += add;
    }
    if(ss > qe || qs > se) return 0;
    if(qs <= ss && qe >= se) return st[si];
    ll mid = ss + (se-ss)/2;
    return lazyPropQuery(st,lazy,2*si,ss,mid,qs,qe) + lazyPropQuery(st,lazy,2*si+1,mid+1,se,qs,qe);
}

void rangeUpdateSegTree(ll a[],ll st[],ll lazy[],ll si,ll ss,ll se,ll qs,ll qe,ll add){
    //You have to update in the original array first
    if(lazy[si] != 0 ){
        ll ad = lazy[si];
        lazy[si] = 0;
        st[si] += (se-ss+1)*ad;
        if(se != ss) lazy[2*si] += ad, lazy[2*si+1] += ad;
    }
    if(ss > qe || qs > se) return;
    if(ss >= qs && se <= qe){
        ll ad = (se-ss+1)*add;
        st[si] += ad;
        if(ss != se) lazy[2*si] += ad, lazy[2*si+1] += ad;
        return;
    }
    ll mid = ss + (se-ss)/2;
    rangeUpdateSegTree(a, st, lazy,  2*si, ss,qs,qe ,mid,add);
    rangeUpdateSegTree(a,st,lazy,2*si+1,mid+1,se,qs,qe,add);
    st[si] = st[2*si] + st[2*si+1];
}


//end of lazy propagation


//start of Mergesort tree

//mrt must be initialised as vector<ll> mrt[N];

void buildMergeSortTree(ll a[],vector<ll> mrt[],ll si,ll ss,ll se){
    if(ss == se){
        mrt[si].push_back(a[ss]);
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildMergeSortTree(a,mrt,2*si,ss,mid);
    buildMergeSortTree(a,mrt,2*si+1,mid+1,se);
    ll i=0,j=0;
    while(i < mrt[2*si].size() && j < mrt[2*si+1].size()){
        if(mrt[2*si][i] <= mrt[2*si+1][j]){
            mrt[si].push_back(mrt[2*si][i]);
            i++;
        }
        else mrt[si].push_back(mrt[2*si+1][j]), j++;
    }
    while(i<mrt[2*si].size()) 
        mrt[si].push_back(mrt[2*si][i]),i++;
    while(j<mrt[2*si+1].size())
        mrt[si].push_back(mrt[2*si+1][j]),j++;
        //The merging can also be done by just one line.
    //merge(mrt[2*si].begin(), mrt[2*si].end(), mrt[2*si+1].begin(), mrt[2*si+1].end(),back_inserter(mrt[2*si]));
}

ll queryMergeSortTree(vector<ll> mrt[],ll si,ll ss,ll se,ll qs,ll qe,ll k){
    if(qe < ss || qs > se) return 0;
    //lower_bound returns an iterator pointing to the first element in the range [first,last) which has a value not less than ‘val’. 
    //upper_bound returns an iterator pointing to the first element in the range [first,last) which has a value greater than ‘val’. 
    if(ss >= qs && qe >= se)
        return (upper_bound(mrt[si].begin(),mrt[si].end(),k-1) - mrt[si].begin());
    
    ll mid = ss + (se-ss)/2;
    return queryMergeSortTree(mrt,2*si,ss,mid,qs,qe,k) + queryMergeSortTree(mrt,2*si+1,mid+1,se,qs,qe,k);
}


//end of merge sort tree


//*************************................................SPARSE TABLES..............................************************

// start of sparse table for a range sum query

ll rsq_sparse(){
    ll N; //is the size of the array
    ll sparsetable[N+1][K+1];
    for(ll i=0;i<N;i++) sparsetable[i][0] = arr[i];

    for (ll j = 1; j <= K; j++)
        for (ll i = 0; i + (1 << j) <= N; i++)
            sparsetable[i][j] = sparsetable[i][j-1] + sparsetable[i + (1 << (j - 1))][j - 1];
    ll sum = 0;
    for (ll j = K; j >= 0; j--) {
        if ((1 << j) <= R - L + 1) {
            sum += sparsetable[L][j];
            L += 1 << j;
     }
    }
    return sum;
}

// end of parse table for range sum query

int32_t main()
{
    fastio;
    cout << "HI";
    //Segment Tree
    return 0;
}
