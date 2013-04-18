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

#define MAXN 1005

struct Union{
	int p[MAXN];
	int nset;
	Union(int n){
		rep(i,n)
			p[i] = i;
		nset = n;
	}
	int merge(int a, int b){
		int pa = get(a), pb = get(b);
		if(pa == pb)
			return false;
		p[pa] = pb;
		nset--;
		return true;
	}
	int get(int at){
		return p[at] = (p[at] == at ? at : get(p[at]));
	}
	bool same(int a, int b){
		return get(a) == get(b);
	}
};

int main(){
while(1){
	int n,m,nblue;
	cin >> n >> m >> nblue;
	if(n==0)
		break;
	vector<pair<int,int> > red;
	int blue_used = 0;
	int ncon = n;
	Union blue_union(n);
	rep(i,m){
		char c;
		int a,b; 
		cin >> c >> a >> b;
		a--; b--;
		if(c == 'B'){
			if(blue_union.merge(a,b)){
				blue_used++;
				ncon--;
			}
		} else{
			red.pb(mp(a,b));
		}
	}
	Union red_union(n);
	rep(i, sz(red)){
		if(blue_used == nblue && ncon == 1)
			break;
		int a = red[i].F, b = red[i].S;
		if(blue_union.same(a,b)){
			if(blue_used > nblue){
				if(!red_union.same(a,b)){
					red_union.merge(a,b);
					blue_used--;
				}
			}
		} else {
			red_union.merge(a,b);
			blue_union.merge(a,b);
			ncon--;
		}
	}
	//cout << blue_used << " " << ncon << endl;
	cout << (blue_used == nblue && ncon == 1? '1' : '0') << endl;
}
}
