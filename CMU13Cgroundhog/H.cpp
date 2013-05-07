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

struct Node{
	multimap<ll,ll> dat;
	ll a, b;
	Node *left, *right;
	Node(vector<ll>& v, ll low, ll high){
		a = v[low], b = v[high-1];
		if(low + 1 == high){
			left = right = NULL;
			return;
		}
		ll m = (low + high)/2;
		left = new Node(v, low, m);
		right = new Node(v, m, high);
	}

	void insert(ll x, ll y, ll index){
		if(x < a || x > b)
			return;
		dat.insert(mp(y,index));
		if(left && right){
			left->insert(x,y,index);
			right->insert(x,y,index);
		}
	}

	void query(ll xa, ll xb, ll ya, ll yb, vector<ll>& res){
		if(xa <= a && xb >= b){
			for(auto it = dat.lower_bound(ya); it != dat.upper_bound(yb); it++)
				res.pb(it->S);
		} else if(xa > b || xb < a){

		} else{
			left->query(xa,xb,ya,yb,res);
			right->query(xa,xb,ya,yb,res);
		}
	}
};

#define SQ(x) ((x)*(x))

int main(){
	set<ll> exes;
	ll n; cin>>n;
	vector<ll> X(n), Y(n), R(n);
	rep(i,n){
		cin >> X[i] >> Y[i] >> R[i];
		exes.insert(X[i]);
	}
	vector<ll> ux;
	foreach(it, exes)
		ux.pb(*it);

	Node* root = new Node(ux, 0, sz(ux));

	rep(i,n)
		root->insert(X[i], Y[i], i);

	set<pair<int,int> > seen;

	ll res = 0;
	rep(i, n){
		vector<ll> v;
		root->query(X[i] - 2*R[i], X[i] + 2*R[i], Y[i] - 2*R[i], Y[i] + 2*R[i], v);
		foreach(it, v){
			pair<int,int> cur = mp(i, *it);
			if(cur.F > cur.S)
				swap(cur.F, cur.S);
			if(seen.insert(cur).S)
				if(SQ(X[*it] - X[i]) + SQ(Y[*it] - Y[i]) == SQ(R[i] + R[*it]))
					res++;
		}
	}

	cout << res << endl;

}	
