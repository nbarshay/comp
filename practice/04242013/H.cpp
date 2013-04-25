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

template<class T>
ostream& operator<<(ostream& out, vector<T> v){
	out << "[";
	rep(i, sz(v)){
		if(i) out << ", ";
		out << v[i];
	}
	out << "]";
	return out;
}
template<class A, class B>
ostream& operator<<(ostream& out, pair<A,B> p){
	out << "<" << p.F << ", " << p.S << ">";
	return out;
}
template<class T>
ostream& operator<<(ostream& out, set<T> s){
	out << "(";
	foreach(it, s){
		if(it != s.begin()) out << ", ";
		out << *it;
	}
	out << ")";
	return out;
}
template<class A, class B>
ostream& operator<<(ostream& out, map<A,B> m){
	out << "{";
	foreach(it, m){
		if(it != m.begin()) out << ", ";
		out << *it;
	}
	out << "}";

}

typedef long long ll;

const ll MAXN = 2000;

ll p[MAXN];
ll r[MAXN];
ll w[MAXN];
ll d[MAXN];

void init(ll n){
	rep(i,n)
		p[i] = i;
	rep(i,n)
		r[i] = 0;
	rep(i, n)
		w[i] = -1;
}

ll get(ll at){
	return p[at] == at ? at : get(p[at]);
}

bool merge(ll a, ll b, ll cost){
	ll pa = get(a), pb = get(b);
	if(pa == pb)
		return false;
	if(r[pa] < r[pb])
		swap(pa, pb);
	r[pa] = max(r[pb]+1, r[pa]);
	p[pb] = pa;
	w[pb] = cost;
	return true;
}

int rec(ll at){
	if(d[at] >= 0)
		return d[at];
	if(p[at] == at)
		return 0;
	else
		return d[at] = rec(p[at]) + 1;
		
}

ll do_dfs(ll n){
	rep(i,n)
		d[i] = -1;
	rep(i,n)
		rec(i);
}

ll query(ll a, ll b){
	ll res = 0;
	while(d[a] > d[b]){
		res = max(res, w[a]);
		a = p[a];
	}
	while(d[b] > d[a]){
		res = max(res, w[b]);
		b = p[b];
	}
	while(a != b){
		res = max(res, w[b]);
		res = max(res, w[a]);
		a = p[a];
		b = p[b];
	}
	return res;
}

const ll inf = 1000000000000000000LL;

int main(){
ll n,m;
while(cin >> n >> m){
	vector<pair<ll, pair<ll,ll> > > e;
	rep(i,m){
		ll a,b,c; cin>>a>>b>>c;
		a--; b--;
		e.pb(mp(c, mp(a,b)));
	}
	sort(e.begin(), e.end());
	init(n);
	ll cur = 0;
	rep(i, m){
		if(merge(e[i].S.F, e[i].S.S, e[i].F)){
			cur += e[i].F;
		}
	}
	set<ll> parent;
	rep(i,n)
		parent.insert(get(i));
	if(sz(parent) != 1){
		printf("disconnected\n");
		continue;
	}

	do_dfs(n);


	ll ans = inf;
	rep(i,m){
		ans = min(ans, cur - query(e[i].S.F, e[i].S.S) - e[i].F);
	}

	cout << ans << endl;
}
}	
