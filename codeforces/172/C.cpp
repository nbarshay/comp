#define _GLIBCXX_DEBUG
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


vector<vector<int> > adj;
vector<int> dist;


void dfs(int at, int from, int d){
	dist[at] = d;
	for(int to : adj[at]) if(to != from)
		dfs(to, at, d+1);
}

int main(){
	int N; cin>>N;
	adj = vector<vector<int> >(N);
	dist = vector<int>(N);
	rep(i, N-1){
		int a,b; cin>>a>>b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(0,-1,0);
	double res = 0.0;
	rep(i, N){
		res += 1.0/(dist[i]+1);
	}
	cout << fixed << setprecision(8) << res << endl;
}	
