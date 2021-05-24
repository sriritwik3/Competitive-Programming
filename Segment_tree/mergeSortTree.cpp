//#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<limits.h>
#include<vector>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

//mrt must be initialised as vector<ll> mrt[4*N];

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

int32_t main()
{
    fastio;
    cout << "HI";
    //Segment Tree
    return 0;
}
