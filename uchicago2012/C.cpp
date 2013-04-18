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

ll gcd(ll a, ll b){
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

int main(){
while(1){
	ll n,k; cin>>n>>k;
	if(n==0 && k==0)
		break;
	vector<vector<ll> > loc(k);
	rep(i,n){
		loc[i%k].pb(i);
	}
	vector<ll> cat;
	foreach(it, loc){
		vector<ll>& cur = *it;
		for(ll i = sz(cur)-1; i>=0; i--)
			cat.pb(cur[i]);
	}
	vector<ll> cyc(n);
	rep(i,n) cyc[cat[i]] = i;
	ll res = 1;
	vector<bool> V(n,false);
	rep(i,n) if(!V[i]){
		ll len = 0;
		ll at = i;
		while(!V[at]){
			len++;
			V[at] = true;
			at = cyc[at];
		}
		//cout << len << endl;
		res = (res/gcd(res, len)) * len;
	}
	cout << res << endl;
}
}	
