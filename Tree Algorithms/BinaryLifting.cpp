#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
const int M = 1e9+7;

// #include <ext/pb_ds/assoc_container.hpp> // Common file
// #include <ext/pb_ds/tree_policy.hpp>
// #include <ext/pb_ds/detail/standard_policies.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key

#define lld long double
#define ll long long
typedef unsigned long long ull;


ll pow(ll a,ll b,ll m = M) {a %= m;ll res = 1;while (b>0) {if(b&1)res = res * a % m;a = a * a % m;b >>= 1;}return res;}
ll mod_add(ll a,ll b,ll m = M) {a%=m,b%=m; return (a+b)%m;}
ll mod_sub(ll a,ll b,ll m = M) {a%=m,b%=m; return (a-b+m)%m;}
ll mod_mul(ll a,ll b,ll m = M) {a%=m,b%=m; return (a*1ll*b)%m;}
ll mod_div(ll a,ll b,ll m = M) {a%=m,b%=m; ll binv = pow(b,m-2,m); return mod_mul(a,binv,m);}

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
// void _print(pbds v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}




void dfs(int node,int pp,vector<int>adj[],vector<vector<int>>&par){
	par[node][0] = pp; //base case for binary lifting

	//for trees we can calculate all 2^xthe par of each node as we go down dfs
	//this is because par[node][x] = par[par[node][x-1]][x-1]
	//it requires ancestor nodes 2^x-1 info, which we are sure will be calculated because we go top to down
	//so basically any node is dependent on the ancestor nodes only

	// for(int x = 1;x<20;++x){
	// 	par[node][x] = par[par[node][x-1]][x-1]; 
	// }

	for(auto &it : adj[node]){
		if(it != pp){
			dfs(it,node,adj,par);
		}
	}
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("Error.txt","w",stderr);
#endif
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   
   int n;cin >> n;
   vector<int>*adj = new vector<int>[n];

   for(int i = 0;i<n-1;++i){
   	int u,v;cin >> u >> v;
   	adj[u].push_back(v);
   	adj[v].push_back(u);
   }

   vector<vector<int>>par(n+1,vector<int>(20));

   dfs(1,0,adj,par);

   //the generic way which is applicable for directed graphs also
   //in general we dont know that any nodes 2^x-1 ancestor nodes is calculated for sure, because we can start dfs from any point and there can be cycle and all which can cause problem
   //so better is parallely calculate 2^x for each node one by one
   //i.e. we know the base case i.e. 2^0th parent and after that we can go on building one by one for all nodes in the graph
   //here as we are bulding step by step for all nodes then we are sure that at an point if we are calculating 2^xth of any node then we will need 2^x-1 of that nodes 2^x-1th parent 
   //but we dont care what is the ancestor and all as we if we calculating 2^xth our implementation makes sure that all other nodes 2^xth par is calculated
   //this is nothing but dp approach only


   //generic implementation
   for(int x = 1;x<20;++x){
   	for(int node = 1;node<=n;++node){
   		par[node][x] = par[par[node][x-1]][x-1];
   	}
   }

   /*most common applications(as far as I recall right now there can be more but mostly originating from these below)
	   1. classical LCA of two nodes in logN
	   2. prefix sums on tree like questions
	   3. path aggregates i.e. path gcd,maximum,minimum,etc
	   4. partial sums on trees

	   mostly can solve problems where static path queries are involves
	   if there are update then we can use euler tour + any range query ds
   */


   
   cout<<1;
}