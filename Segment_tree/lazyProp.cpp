//#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<limits.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

// segment Tree passing as an argument

void buildSegmentTree(ll a[],ll st[],ll si,ll ss, ll se){
    if(ss == se){
        st[si] = a[se];
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildSegmentTree(a,st,2*si,ss,mid);
    buildSegmentTree(a,st,2*si+1,mid+1,se);
    st[si] = st[2*si] + st[2*si+1];
}

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


int32_t main()
{
    fastio;
    cout << "HI";
    //Segment Tree
    return 0;
}
