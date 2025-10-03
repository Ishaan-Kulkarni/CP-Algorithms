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



const int N = 2e5 + 10;

int m[N][25];
int logg[N];


void build(int n){
    //build sparse table
    //m[i][j] = min(m[i][j-1],[i+(1<<(j-1))][j-1])

    for(int i = n-1;i>=0;i--){
        for(int j = 1;j<25;++j){
            if(i+(1<<(j-1)) < n){
                m[i][j] = min(m[i][j-1],m[i+(1<<(j-1))][j-1]);
            }
        }
    }
}


//O(log(R-L+1))
// int query(int L,int R){
//     int len = R - L + 1;
//     int ans = INT_MAX;
    
//     for(int i = 0;i<25;++i){
//         if(len & (1<<i)){
//             ans = min(ans,m[L][i]);
//             L += (1<<i);
//         }
//     }
    
//     return ans;
// }

int query(int L,int R){
    //logic for O(1) is we dont care about disjoint intervals we directly take the largest power of 2 that fits in that interval
    
    int k = logg[R-L+1];
    int ans = min(m[L][k],m[R - (1<<k) + 1][k]);
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("Error.txt","w",stderr);
#endif
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   
    //implementation of sparse table
    
    int n,q;cin >> n >> q;
    vector<int>v(n);
    for(int i = 0;i<n;++i) {
        cin >> m[i][0];
    }
    
    build(n);
    
    logg[1] = 0;
    for(int i = 2;i<=N;++i){
        logg[i] = 1 + logg[i/2];
    }
    
    while(q--){
        int L,R;
        cin >> L >> R;
        L--;R--;
        
        cout << query(L,R) << '\n';
        
    }
    
    
    

}

