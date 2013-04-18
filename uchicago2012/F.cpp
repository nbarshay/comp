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
	ll a,b;
	ll sum;
	Node* left;
	Node* right;
	Node(ll _a, ll _b){
		a = _a, b = _b;
		if(a + 1 == b){
			sum = 1;
			left = right = NULL;
		} else{
			ll m = (a+b)/2;
			left = new Node(a, m);
			right = new Node(m,b);
			sum = left->sum + right->sum;
		}
	}
	ll sub(ll loc){
		if(loc >= a && loc < b){
			if(right && left){
				left->sub(loc);
				right->sub(loc);
				sum = left->sum + right->sum;
			} else{
				sum = 0;
			}
		} else{
		}
	}
	ll get(ll low, ll high){
		if(high <= a || low >= b){
			return 0;
		} else if(low <= a && high >= b){
			return sum;
		} else{
			return left->get(low,high) + right->get(low, high);
		}
	}
};

Node* root;
ll n;

ll query(ll a, ll b){
	if(b > a){
		return root->get(a+1, b);
	} else{
		return root->get(a+1, n) + root->get(0, b);
	}
}

int main(){
while(1){
	cin>>n;
	if(n==0)
		break;
	vector<ll> loc(n);
	rep(i,n){
		ll t; cin>>t;
		loc[t-1] = i;
	}
	root = new Node(0,n);

	ll at = 0;
	ll res = 0;
	rep(i, n){
		ll to = loc[i];
		ll a,b;
		ll hit;
		if(at != to){
			a = query(at, to) + (i == 0 ? 1 : 0);
			b = query(to, at) + 1;
			hit = min(a,b);
		} else{
			hit = 0;
		}

		//cout << "HIT: " << hit << endl;
		res += hit;	
		res += 1;
		root->sub(to);
		at = to;
	}
	cout << res << endl;
}
}	
