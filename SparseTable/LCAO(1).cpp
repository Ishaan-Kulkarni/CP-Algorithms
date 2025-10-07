
//problem link : https://www.spoj.com/problems/LCASQ/


#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;

vector<int>adj[N];
vector<int>flat;
vector<int>depth;
int m[N][20];
int logg[N];
map<int,int>mpp;//to store the first index of the node in flat
int timer;

void dfs(int node,int pp,int d){
    
    flat.push_back(node);
    if(pp != -1) depth.push_back(d);
    else depth.push_back(0);
    mpp[node] = timer++;
    for(auto &it : adj[node]){
        if(it != pp){
            dfs(it,node,d+1);
            depth.push_back(d);
            flat.push_back(node);
            timer++;
        }
    }
}

int main()
{
    int n;cin >> n;
    
    
    logg[1] = 0;
    
    for(int i = 2;i<N;++i){
        logg[i] = 1 + logg[i/2];
    }
    
    for(int i = 0;i<n;++i){
        int ch;
        cin >> ch;
        for(int j = 0;j<ch;++j){
            int ch;cin >> ch;
            adj[i].push_back(ch);
            adj[ch].push_back(i);
        }
    }

    dfs(0,-1,0);
    // for(auto &i : flat) cout << i << ' ';
    // cout << '\n';
    // for(auto &i : depth) cout << i << ' ';
    
    //build sparse table for depth (lets store index)
    for(int i = 0;i<depth.size();++i){
        m[i][0] = i;
    }
    
    int nn = depth.size();
    for(int i = nn-1;i>=0;i--){
        for(int j = 1;j<20;++j){
            if(i+(1<<j) < nn){
                int f = depth[m[i][j-1]];int s = depth[m[i+(1<<(j-1))][j-1]];
                m[i][j] = (f<s) ? m[i][j-1] : m[i+(1<<(j-1))][j-1];
            }
        }
    }
    
    // cout << '\n';
    
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        int L = min(mpp[u],mpp[v]);
        int R = max(mpp[u],mpp[v]);
        
        //biggest power of 2 that can fit into this interval
        int len = (R-L+1);
        int j = logg[len];
        int ind1 = m[L][j],ind2 = m[R-(1<<j)+1][j];
        int min_ind = (depth[ind1] < depth[ind2]) ? ind1 : ind2;
        cout << flat[min_ind] << '\n';
        
    }

    return 0;
}
