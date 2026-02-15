
#include <bits/stdc++.h>
using namespace std;

#define ll long long


//solving distinct queries using Mo's algo (offline quries)

//why the Mo's algo complexity is less
//the reason is when we sort the queries by (L/BLK_SZ,R) then when we go from one query to another query in the block then the max change that can happen on the left side (L) is root(N)
//Because those queries are in the same block and each block size is root(N), i.e. for every query L will move root(N)
//For the right side R it can go maximum N for each block because R is increasing
//lets say there are some x out of q queries in first block then R will move O(N) overall for that x queries in that block
////i.e. for every block no matter how many queries as R is increasing (sorting ensures it) it will move at max O(N)
//therefore its complexity is O(N*root(N))

/* IMP 
//the imp part in Mo's also is about R that R is increasing and will move O(N) for each block (no matter how many queries, it wll move O(N))
//and it will be root(N) times only because there are root(N) blocks
*/

//Also one more imp point is that while shifting blocks i.e. when we go to diff block i.e. l,r are now in diff block then that resetting also take O(N*root(N))
//what it means is lets say for 1st block R is increasing and goes till N-1 and for second block the R have to again come push_back
//so its like for every block at worst case R is shifting from N-1 to 0, so we can say that backward moment total for all quries would be O(N*root(N))
//obviously it will be less than O(N*root(N))


//therefore total complexity is O(N*root(N) + Q*root(N)) === O((N+Q)*root(N))


//questions :-
//Q1 CSES Distinct queries : https://cses.fi/problemset/task/1734
//Q2 SPOJ - DQUERY : https://www.spoj.com/problems/DQUERY/

const int N = 1000005;
ll BLK_SZ;
ll f[N];
ll tans;

bool cmp(vector<int>&a,vector<int>&b){
    if(a[0]/BLK_SZ == b[0]/BLK_SZ) return a[1] < b[1];
    return a[0]/BLK_SZ < b[0]/BLK_SZ;
}


void insert(int num){
    f[num]++;
    if(f[num] == 1) tans++;
}

void remove(int num){
    f[num]--;
    if(f[num] == 0) tans--;
}


int main()
{
    
    int n,q;
    cin >> n;
    
    vector<int>v(n);
    for(auto &i : v) cin >> i;
    
    vector<vector<int>>qu;
    cin >> q;
    BLK_SZ = ceil(sqrt(n));
    
    int ind = 0;
    while(ind < q){
        int l,r;
        cin >> l >> r;
        l--;r--;
        qu.push_back({l,r,ind});
        ind++;
    }
    tans = 0;
    
    sort(qu.begin(),qu.end(),cmp);
    
    vector<int>ans(q);
    int s = 0,e = -1; //[0,-1] -> empty range
    for(auto &it : qu){
        int l = it[0],r = it[1],ind = it[2];
        
        //first insert
        while(e<r){
            e++;
            insert(v[e]);
        }
        while(s>l){
            s--;
            insert(v[s]);
        }
        
        
        //then remove
        while(e>r){
            remove(v[e]);
            e--;
        }
        while(s<l){
            remove(v[s]);
            s++;
        }
        ans[ind] = tans;
    }
    
    for(auto &i : ans) cout << i << '\n';
    
    

    return 0;
}
