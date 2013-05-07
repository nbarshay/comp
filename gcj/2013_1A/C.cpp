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

#define TWO(x) (1<<(x))

const int MAXC = 6;
const int MAXP = 126;
double mem[MAXC][MAXC][MAXC][MAXP];

int main(){

rep(a, MAXC) rep(b, MAXC) rep(c, MAXC){
	int v[3] = {a,b,c};
	rep(i, MAXP) 
		mem[a][b][c][i] = 0;
	rep(k, TWO(3)){
		int prod = 1;
		rep(j,3) if(k&TWO(j))
			prod *= v[j];
		assert(prod < MAXP);
		mem[a][b][c][prod] += double(1)/double(TWO(3));
	}
}

int cases; cin>>cases;
rep(cas, cases){
	int r,n,m,p; cin>>r>>n>>m>>p;
	printf("Case #%d:\n", cas+1);
	assert(n == 3);
	assert(m < MAXC);
	rep(tcase, r){
		vector<int> K(p);
		rep(i, p)
			cin >> K[i];
		int ba, bb, bc;
		double best_prob = -1.0;
		For(a,2, m+1) For(b,2, m+1) For(c,2, m+1){
			double prob = 1.0;
			rep(i, p){
				prob *= mem[a][b][c][K[i]];
			}
			if(prob > best_prob){
				ba = a, bb = b, bc = c;
				best_prob = prob;
			}
		}
		printf("%d%d%d\n", ba, bb, bc);
	}
}
}	
