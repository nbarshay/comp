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

const int MAXD = 105;
const int MAXL = 1005;

int n,m;
bool V[MAXD][MAXD][MAXL];
string s;
vector<string> B;

int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};

bool rec(int r, int c, int loc){
	if(loc == sz(s))
		return true;
	if(r < 0 || c < 0 || r >=n || c >= m || B[r][c] != s[loc])
		return false;
	if(V[r][c][loc])
		return false;
	V[r][c][loc] = true;
	rep(d,4){
		if(rec(r+dr[d], c+dc[d], loc+1))
			return true;
	}
	return false;
}


int main(){
	cin >> n >> m;
	rep(i, n){
		string t; cin >> t;
		assert(sz(t) == m);
		B.pb(t);
	}
	int t; cin>>t;
	rep(i,t){
		cin >> s;
		rep(i, n) rep(k,m) rep(j, sz(s) + 2)
			V[i][k][j] = false;
		bool got = false;
		rep(i,n) rep(k,m){
			if(rec(i,k,0))
				got = true;
		}
		cout << (got ? "YES" : "NO") << endl;
	}

}	
