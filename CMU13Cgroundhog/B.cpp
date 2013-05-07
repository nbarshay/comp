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

int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

int main(){
	int n,m; cin>>n>>m;
	int r,c; cin>>r>>c;
	vector<vector<int> > H(n, vector<int>(m));
	rep(i,n)
		rep(k,m) cin>>H[i][k];
	r--; c--;
	int dir = 2;
	while(1){
		vector<pair<pair<int,int>, pair<int,pair<int,int> > > > opt;
		rep(k,3){
			int d;
			if(k == 0) d = dir;
			if(k == 1) d = dir+1;
			if(k == 2) d = dir+3;
			d = d % 4;
			int tr = r+dr[d], tc = c+dc[d];
			if(tr < 0 || tc < 0 || tr >= n || tc >= m)
				continue;
			if(H[tr][tc] >= H[r][c])
				continue;
			opt.pb(mp(mp(H[tr][tc], k), mp(d, mp(tr,tc))));
		}
		sort(opt.begin(), opt.end());
		if(sz(opt) == 0)
			break;
		dir = opt[0].S.F, r = opt[0].S.S.F, c = opt[0].S.S.S;
	}
	cout << (r+1) << " " << (c+1) << endl;
}	
