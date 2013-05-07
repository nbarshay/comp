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


vector<vector<int> > adj;
vector<bool> vis;
bool bad;

void dfs(int at){
	if(vis[at]){
		bad = true;
	}else{
		vis[at] = true;
		foreach(it, adj[at])
			dfs(*it);
	}

}


int main(){
int np; cin>>np;
rep(tp,np){
	int n; cin>>n;
	adj = vector<vector<int> >(n);
	rep(i,n){
		int t; cin>>t;
		rep(k,t){
			int a; cin>>a;
			a--;
			adj[i].pb(a);
		}
	}
	
	bad = false;
	rep(i,n){
		vis = vector<bool>(n, false);
		dfs(i);
	}
	
	printf("Case #%d: %s\n", tp+1, bad ? "Yes" : "No");
}
}	

