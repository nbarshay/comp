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
	return out;
}

int main(){
	int N,D; cin>>N>>D;
	vector<int> X(N), Y(N);
	vector<int> A(N,0);
	For(i,1,N-1)
		cin >> A[i];
	rep(i,N)
		cin >> X[i] >> Y[i];
	
	vector<int> dist(N, -1);
	vector<int> vis(N, false);
	dist[N-1] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push(mp(0,N-1));
	while(!pq.empty()){
		int at = pq.top().S;
		pq.pop();
		if(vis[at])
			continue;
		vis[at] = true;
		rep(i,N) if(i != at){
			int len  = abs(X[at] - X[i]) + abs(Y[at] - Y[i]);
			int hit = max(dist[at] + len*D - A[i], 0);
			if(dist[i] == -1 || hit < dist[i]){
				dist[i] = hit;
				pq.push(mp(dist[i], i));
			}
		}
	}
	cout << dist[0] << endl;
}	
