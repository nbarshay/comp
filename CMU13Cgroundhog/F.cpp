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

int main(){
	int n,f; cin>>n>>f;	
	vector<string> V(n);
	rep(i,n)
		cin >> V[i];
	vector<int> rows;

	rep(i,n){
		bool got = false;
		rep(k,n) 
			if(V[i][k] == 'x')
				got = true;
		if(got)
			rows.pb(i);
	}

	rep(ridx, sz(rows)){
		int r = rows[ridx];
		int cnt = 0;
		vector<int> pos;
		rep(c,n) if(V[r][c] == 'x')
			pos.pb(c);
		int need = min(sz(pos), f);
		int lowr = ridx == 0 ? 0 : rows[ridx-1] + 1; int highr = (need == f) ? n-1 : r;
		rep(i, need){
			int lowc = (i == 0) ? 0 : pos[i-1] + 1;
			int highc = (i == need-1) ? (n-1) : pos[i];
			//cout << lowr << " " << highr << " " << lowc << " " << highc << endl;
			cout << (lowc) << " " << (n - highr - 1) << " " << (highc + 1) << " " << (n - lowr) << endl;
		}
		f -= need;
	}
	assert(f == 0);
}	
