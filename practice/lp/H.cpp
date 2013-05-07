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
#include <iomanip>
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

#define SQ(x) ((x)*(x))
const double inf = 1e10;

#define MAXN 105
double D[MAXN];
int B[MAXN];
vector<pair<pair<int,int>, double> > edges;
vector<bool> used;

int V[MAXN];

int dfs(int at){
	if(V[at])
		return at;
	V[at] = true;

	int e = B[at];

	int hit = dfs(edges[e].F.F);
	if(hit == -1)
		return hit;

	swap(edges[e].F.F, edges[e].F.S);
	edges[e].S *= -1;
	used[e] = !used[e];

	if(hit == at)
		return -1;
	else
		return hit;
}

int main(){
	int tp = 0;

	int n;
	while(cin >> n){
		if(n==0)
			break;
		double bonus, cost;
		cin >> bonus >> cost;

		vector<int> X(n), Y(n);
		vector<vector<int> > adj(n);
		rep(i,n){
			cin >> X[i] >> Y[i];
			int t;
			while(1){
				cin >> t;
				if(t == 0)
					break;
				adj[i].pb(t - 1);
			}
		}

		edges.clear();	
		rep(i,n) foreach(it, adj[i]){
			double val = sqrt(SQ(X[i]-X[*it]) + SQ(Y[i] - Y[*it]))*bonus - cost;
			edges.pb(mp(mp(i, *it), val));
		}
		used = vector<bool>(sz(edges), false);
		
		while(true){
			rep(i,n)
				D[i] = -inf;	
			D[0] = 0.0;
			rep(ridx,n){
				rep(i, sz(edges)) {
					int a = edges[i].F.F, b = edges[i].F.S;
					double c = edges[i].S;
					if(D[a] + c > D[b]){
						D[b] = D[a] + c;
						B[b] = i;
					}
				}
			}

			bool didit = false;
			rep(i, sz(edges)) {
				int a = edges[i].F.F, b = edges[i].F.S;
				double c = edges[i].S;
				if(D[a] + c > D[b]){
					memset(V,0,sizeof(V));
					int hit = dfs(a);
					assert(hit == -1);

					didit = true;
					break;
				}
			}
			if(!didit)
				break;
		}
		double ans = 0.0;
		rep(i, sz(edges)) if(used[i])
			ans += -edges[i].S;
		cout << "Case " << ++tp << ": " << fixed << setprecision(2) << ans << endl;
	}
}	
