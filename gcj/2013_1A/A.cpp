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

bool safeMul(ll a, ll b, ll& c){
	c = a*b;
	if(a != 0 && c / a != b){
		return false;
	}
	return true;
}

int main(){
int cases; cin>>cases;
rep(cas, cases){
	ll rad, paint; cin>>rad>>paint;
	ll a = 1, b = 4*707106780LL + 5;
	while(a != b){
		ll m = (a+b+1)/2;
		ll a1 = 2*rad + 1;
		ll a2 = 2*rad + 1 + 4*(m-1);
		ll res;
		bool safe = safeMul(m, a1+a2, res);
		if(!safe || res/2 > paint)
			b = m-1;
		else
			a = m;
	}
	printf("Case #%d: %lld\n", cas+1, a);
}
}	
