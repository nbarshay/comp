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
#define MAXN 505
#define MAXM 10005

int parent[MAXN];
int init(int cnt){
	rep(i, cnt)
		parent[i] = i;
}
int get(int at){
	return (parent[at] = (parent[at] == at ? at : get(parent[at])));
}
bool merge(int a, int b){
	int pa = get(a);
	int pb = get(b);
	if(pa == pb)
		return false;
	parent[pa] = pb;
	return true;
}

int main(){
	int n,m; cin >> n >> m;
	vector<pair<int,int> > e;
	rep(i,m){
		int a,b; cin>>a>>b;
		a--; b--;
		e.pb(mp(a,b));
	}
	int pre_walk[MAXM];
	init(n);
	rep(i, m){
		if(merge(e[i].F, e[i].S)){
			pre_walk[i] = i;
		} else{
			assert(i);
			pre_walk[i] = pre_walk[i-1];
		}
	}
	int post_walk[MAXM];
	init(n);
	for(int i = m-1; i>= 0; i--){
		if(merge(e[i].F, e[i].S)){
			post_walk[i] = i;
		} else{
			assert(i != m-1);
			post_walk[i] = post_walk[i+1];
		}
	}
	int nq; cin>>nq;
	rep(i, nq){
		int res = n;
		init(n);
		int a,b; cin>>a>>b;
		a--; b--;
		int at = a-1;
		vector<int> use;
		while(at != -1){
			if(pre_walk[at] == at){
				use.pb(at);
				at--;
			}else{
				at = pre_walk[at];
			}
		}
		at = b+1;
		while(at != m){
			if(post_walk[at] == at){
				use.pb(at);
				at++;
			} else{
				at = post_walk[at];
			}
		}
		foreach(it, use)
			if(merge(e[*it].F, e[*it].S))
				res--;
		cout << res << endl;
	}

}	
