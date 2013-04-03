#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <deque>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <queue>
#include <cstring>
#include <stack>
#include <assert.h>
using namespace std;

#define IT(c) typeof((c).begin())

#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)
#define foreach(i, c) for(IT(c) i = (c).begin(); i != (c).end(); ++i)

#define sz(a) int((a).size())
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef vector<int> Vi;
typedef vector<vector<int> > Vvi;
typedef vector<string> Vs;
typedef pair<int, int> Pi;

const int MAXN = 30005;


vector<vector<int> > adj;

int P[MAXN];
int T[MAXN];

int get(int at){
	return P[at] = (P[at] == at ? at : get(P[at]));
}

bool merge(int a, int b){
	int pa = get(a);
	int pb = get(b);
	if(pa == pb)
		return false;
	P[pa] = pb;
	return true;
}


int pre[MAXN];
int low[MAXN];
int npre;

void dfs(int at, int from, stack<int>& st){
	pre[at] = npre++;
	low[at] = pre[at];
	st.push(at);
	
	foreach(it, adj[at]) if(*it != from){
		if(pre[*it] == -1)
			dfs(*it, at, st);
		low[at] = min(low[at], low[*it]);
	}

	if(low[at] == pre[at]){
		vector<int> v;
		int last = -1;
		while(last != at){
			last = st.top(); st.pop();
			v.pb(last);
		}

		rep(i, sz(v)-1)
			merge(v[i], v[i-1]);
		T[get(v[0])] = from;
		//cout << get(v[0]) << "-->" << from <<endl;
	}
}

int main(){
	int n,m; cin>>n>>m;
	adj = vector<vector<int> >(n);

	//prep union
	rep(i,n) P[i] = i;

	//prep dfs
	memset(pre,-1,sizeof(pre));
	npre = 0;

	rep(i,m){
		int a,b; cin>>a>>b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	stack<int> st;
	dfs(0, -1, st);

	int nq; cin>>nq;

	rep(tq,nq){
		int t,a,b; cin>>t>>a>>b;
		a--; b--;
		if(t == 1){
			//cout <<"GET: " << get(a)<<" " <<get(b)<<endl;
			cout << (get(a) == get(b) ? '0' : '1') << endl;
		} else{
			int at[2] = {a,b};
			map<int,int> m[2];
			int res[2];
			for(int iter = 0; true ; iter++){
				//cout << at[0] <<" " << at[1] << endl;
				bool done = false;
				rep(k,2){
					if(at[k] != -1){
						at[k] = get(at[k]);
						m[k][at[k]] = iter;
						if(m[1-k].count(at[k])){
							res[k] = iter;
							res[1-k] = m[1-k][at[k]];
							done = true;
						}
						at[k] = T[at[k]];
					}
				}
				if(done)
					break;
			}
			//cout << "RES: " << res[0]  << " " << res[1] << endl;
			int root[2];
			rep(k,2){
				int at = (k == 0) ? a : b;
				rep(i, res[k]){
					at = get(at);	
					int next = T[at];
					bool merged = merge(at, next);
					assert(merged);
					at = next;
				}

				root[k] = get(at);
			}
			//cout << "ROOTS: " << root[0] << " " << root[1] << endl;
			assert(root[0] == root[1]);
			T[get(root[0])] = T[root[0]];
		}
	}


}	

