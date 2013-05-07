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
	int t, n, p; cin >> t >> n >> p;
	vector<int> T(n);
	rep(i,n){
		cin >> T[i];
		T[i]--;
	}
	vector<int> M(n, 0);
	vector<int> S(t,0);
	rep(i, p){
		int a,b; char c; cin>>a>>b>>c;
		a--; b--;
		if(c == 'M')
			M[a]++;
		else{
			if(M[a] < 4){
				S[T[a]]++;
				S[T[b]]--;
			} 
			M[a] = 0;
		}
	}
	int best = -1;
	rep(i, t) best = max(best, S[i]);
	if(S[T[0]] == best){
		cout << ":)" << endl;
		cout << best << endl;
	}
	else{
		cout << ":(" << endl;
		cout << best - S[T[0]] << endl;
	}
}	
