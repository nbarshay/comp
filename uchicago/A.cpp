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

const int MAXN = 1000;

const int inf = 1000000005;

struct Union{
	int p[MAXN];
	int w[MAXN];
	int r[MAXN];
	int d[MAXN];
	int n;

	void init(int _n) {
		n = _n;
		memset(p,-1,n*sizeof(int));
		memset(r,0,n*sizeof(int));
		memset(d,-1,n*sizeof(int));
		memset(w,-1,n*sizeof(int));
	}

	int get(int at){
		return p[at] == -1 ? at : get(p[at]);
	}

	bool merge(int a, int b, int cost){
		int pa = get(a);
		int pb = get(b);
		if(pa == pb)
			return false;

		if(r[pa] < r[pb])
			swap(pa,pb);
		p[pb] = pa;
		w[pb] = cost;
		r[pa] = max(r[pa], r[pb]+1);
		return true;
	}

	void prep(){
		int root = get(0);
		rep(i, n)
			prep_dfs(i);
	}

	int prep_dfs(int at){
		if(d[at] == -1){
			if(p[at] == -1)
				d[at] = 0;
			else
				d[at] = prep_dfs(p[at])+1;
		}
		return d[at];
	}

	int read(int a, int b){
		int big = inf;
		while(d[a] > d[b]){
			big = min(big, w[a]);
			a = p[a];
		}
		while(d[b] > d[a]){
			big = min(big, w[b]);
			b = p[b];
		}
		while(a != b){
			big = min(big, w[a]);
			big = min(big, w[b]);
			a = p[a];
			b = p[b];
		}
		return big;
	}
};

struct Request{
	int type;
	int r,c;
	int a,b,w;
	Request(int _r, int _c) : type(0), r(_r), c(_c) {}
	Request(int _a, int _b, int _w) : type(1), a(_a), b(_b), w(_w) {}
};
struct Edge{
	int a,b; 
	int c;
	int idx;
	bool operator<(const Edge& in) const{
		return c < in.c;
	}
};

int n,m;

void rebuild(Union& u, vector<int>& ord, vector<Edge>& e){
	u.init(n);

	foreach(it, ord){
		u.merge(e[*it].a, e[*it].b, e[*it].c);
	}
	u.prep();
}

vector<Edge> edge;

bool mysort(int a, int b){
	return edge[a].c > edge[b].c;
}

int main(){
	while(1){
		cin>>n>>m;
		if(n==0 && m==0)
			break;
		edge = vector<Edge>(m);
		rep(i,m){
			cin >> edge[i].a >> edge[i].b >> edge[i].c;
			edge[i].a--; edge[i].b--;
			edge[i].idx = i;
		}


		int nq;
		cin>>nq;
		vector<Request> req;
		set<int> imp;
		rep(i, nq){
			char c;
			cin>>c;
			if(c == 'B' || c == 'R'){
				int r,c;
				cin>>r>>c;
				req.pb(Request(r-1,c));
				imp.insert(r-1);
			}
			if(c=='S'){
				int a,b,w;
				cin>>a>>b>>w;
				a--; b--;
				req.pb(Request(a,b,w));
			}
		}

		vector<int> order;
		rep(i,m)
			order.pb(i);
		sort(order.begin(), order.end(), mysort);

		Union u;
		u.init(n);

		foreach(it, order) if(!imp.count(*it)){
			int i = *it;
			if(u.merge(edge[i].a, edge[i].b, edge[i].c)){
				imp.insert(i);
			}
		}

		order.clear();
		foreach(it, imp)
			order.pb(*it);
		sort(order.begin(), order.end(), mysort);

		rebuild(u, order, edge);

		foreach(it, req){
			Request r = *it;	
			if(r.type == 0){
				edge[r.r].c = r.c;

				sort(order.begin(), order.end(), mysort);
				u.init(n);
				rebuild(u,order,edge);
			} else{
				int cap = u.read(r.a, r.b);
				cout << (r.w <= cap ? '1' : '0') << endl;
			}
		}

	}
}	

