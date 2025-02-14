#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
const int M = 1e9+7;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key

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



struct Node{
	//for required aggregate (depends on the given qs)
public:
	int mini,cnt;
public:
	Node() {}
	Node(int mini,int cnt){
		this->mini = mini;
		this->cnt = cnt;
	}
};

Node merge(const Node &a,const Node &b){
	//to define merging logic if we have multiple things to handle in single Node of seg_tree
	if(a.mini == b.mini){
		return Node(a.mini,a.cnt+b.cnt);
	}

	if(a.mini < b.mini){
		return Node(a.mini,a.cnt);
	}

	return Node(b.mini,b.cnt);
}

int NN;
Node t[400010]; //seg_tree

int arr[100010];

void build(int index,int low,int high){
	if(low == high){
		//leaf node
		t[index] =  Node(arr[low],1);
		return;
	}

	int mid = (low+high) / 2;
	build(2*index,low,mid);
	build(2*index+1,mid+1,high); 

	t[index] = merge(t[2*index],t[2*index+1]);//merging logic of seg tree can be modifiable acc to qs
}

void update(int index,int low,int high,int pos,int val){
	if(pos<low || pos>high){
		return;
	}

	if(low == high){
		t[index] = Node(val,1);
		arr[pos] = val;
		return;
	}

	int mid = (low+high)/2;
	update(2*index,low,mid,pos,val);
	update(2*index+1,mid+1,high,pos,val);
	t[index] = merge(t[2*index],t[2*index+1]);

}

Node query(int index,int low,int high,int l,int r){
	//here it can be three cases
	if(low>r || high<l){
		//no overlap
		return Node(INT_MAX,0);
	}
	if(low>=l && high<=r){
		//complete overlap
		return t[index];
	}

	//partial overlap
	int mid = (low+high)/2;
	return merge(query(2*index,low,mid,l,r),query(2*index+1,mid+1,high,l,r));
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("Error.txt","w",stderr);
#endif
   ios_base::sync_with_stdio(false);
   cin.tie(0);

   	int NN;
   	cin >> NN;
   
  	for(int i = 0;i<NN;++i) cin >> arr[i];
  	build(1,0,NN-1);
  	cout<<query(1,0,NN-1,1,1).mini<<" "<<query(1,0,NN-1,1,1).cnt<<"\n";

}
