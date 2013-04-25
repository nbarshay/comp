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
int len, n;
while(cin >> len >> n){
	int fall_left = 0;

	vector<pair<int,char> > v;
	vector<int> pos;
	rep(i,n){
		int t; cin>>t;
		pos.pb(t);
		char c; cin>>c;
		int dist = (c == 'L') ? t : len - t;
		if(c== 'L')
			fall_left++;

		v.pb(mp(dist, c));
	}
	sort(pos.begin(), pos.end());
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	printf("The last ant will fall down in %d seconds - started at ", v[0].F);
	if(n > 1 && v[1].F == v[0].F)
		printf("%d and %d.\n", pos[fall_left-1], pos[fall_left]);
	else{
		int ans;
		if(v[0].S == 'L'){
			ans = pos[fall_left-1];
		} else{
			ans = pos[fall_left];
		}
		printf("%d.\n", ans);
	}
}
}	
