#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <deque>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <stack>
#include <assert.h>
#include <list>
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

typedef long long ll;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef vector<string> VS;
typedef pair<int, int> PI;

vector<vector<int> > adj;
typedef long long ll;

//2IN, INTO
pair<ll,pair<ll,ll> > dfs(int at, int from){
	ll num = 1;
	ll two = 0;
	ll into = 0;

	vector<int> in_two;
	vector<int> in_into;
	int n = sz(adj[at])-1;

	foreach(it, adj[at]) if(*it != from){
		pair<ll, pair<ll,ll> > hit = dfs(*it, at);
		in_two.pb(hit.S.F);
		in_into.pb(hit.S.S);

		num += in.F
	}
	assert(sz(in_two) == n); assert(sz(in_into) == n);



}



int main(){
	rep(i,n){
		int a,b; 
		cin>>a>>b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

}

