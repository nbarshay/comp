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

int procSeg(vector<int> v){
	v.pb(0);
	vector<int> path;
	int res = sz(v);
	rep(i, sz(v)){
		if(v[i] >= sz(path)){
			foreach(it, path)
				(*it)++;
			while(sz(path) < v[i])
				path.pb(1);
		} else{
			sort(path.begin(), path.end());
			vector<int> npath;
			rep(k, v[i])
				npath.pb(path[k]+1);
			For(k, v[i], sz(path))
				res = min(res, path[k]);
			path = npath;	
		}
	}
	return res;
}

int main(){
int np; cin>>np;
rep(tp,np){
	int n; cin>>n;
	int ans = n;

	map<int,int> m;
	rep(i,n){
		int a; cin>>a;
		m[a]++;
	}
	vector<vector<int> > v;
	int last = -1;
	foreach(it, m){
		if(it->F != last+1){
			v.pb(vector<int>());
		}
		v[sz(v)-1].pb(it->S);
		last = it->F;
	}
	foreach(it, v){
		ans = min(ans, procSeg(*it));
	}

	printf("Case #%d: %d\n", tp+1, ans);
}
}	
