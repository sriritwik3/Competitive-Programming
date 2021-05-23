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


int32_t main()
{
    fastio;
    cout << "HI";
    //Segment Tree
    return 0;
}
