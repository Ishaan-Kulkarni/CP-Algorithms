
#include <bits/stdc++.h>
using namespace std;

#define ll long long




//weighted DSU
//each edge has weight like for edge a to b here represents a - b = val

class DisjointSet{
    
    int n;
    vector<int>par,size;
    vector<int>d; //d[x] is the weight from x to par[x]
    
    public:
    DisjointSet(int n){
        this->n = n;
        
        par.resize(n+1);
        d.resize(n+1,0);
        size.resize(n+1,1);
        for(int i = 0;i<=n;++i) par[i] = i;
    }
    
    
    int find(int node){
        if(par[node] == node) return node;
        
        //path compression (but here also the weights will change i.e. add up to the ultimate parent)
        int prev_par = par[node];
        par[node] = find(par[node]);
        d[node] += d[prev_par];
        
        return par[node];
    }
    
    
    //here we will actually answer queries lets say if we get query like x - y = val
    //then we have to first check if both x and y in same comp if yes then we can get ans like (x - representativeofthatset) - (y - representativeofthatset)
    //else we cant we have to merge (union) two of those sets of x and y (this itself is interesting)
    bool unite(int a,int b,int wt){
        int ulp_a = find(a);
        int ulp_b = find(b);
        
        
        if(ulp_a == ulp_b){
            return d[a] - d[b] == wt;  
        }
        
        //the main part here is how to find the wt for the edge between the leaders of the two sets?
        //it is just solving simple equations
        //one thing is for sure that if we any two node oir variables in same component then we can always find the answer for that
        //because there always exists a path in rooted tree
        if(size[ulp_a] > size[ulp_b]){
            par[ulp_b] = ulp_a;
            d[ulp_b] = d[a] + wt - d[b];
            size[ulp_a] += size[ulp_b];
        }
        else{
            par[ulp_a] = ulp_b;
            d[ulp_a] = d[b] - d[a] + wt;
            size[ulp_b] += size[ulp_a];
        }
        return 0;
    }
    
};      


int main()
{
    int t;cin >> t;
    while(t--){
        //here queries will be taken as input
    }

    return 0;
}
