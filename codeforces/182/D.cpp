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

struct Node{
	int a,b;
	int m;
	int cnt;
	Node *left, *right;

	Node(int _a, int _b){
		a = _a, b = _b;
		m = (a+b)/2;
		cnt = 0;
		if(a+1 == b){
			left = right = NULL;
		} else{
			left = new Node(a,m);
			right = new Node(m,b);
		}
	}
	
	int put(int point, int val){
		assert(point >= a && point < b);
		cnt += val;
		if(left && right){
			if(point < m)
				left->put(point, val);
			else
				right->put(point, val);
		}
	}

	int read(int low, int high){
		if(low >= b || high <= a){
			return 0;
		} else if(low <= a && high >= b){
			return cnt;
		} else{
			return left->read(low, high) + right->read(low, high);
		}
	}
};

#define MAXN 200000

struct Fen {
	int fen[MAXN+1];
	inline void upd(int x, int val) {
		x = MAXN-1-x;
		for (; x >= 0; x = (x & (x + 1)) - 1) fen[x] += val;
	}
	inline int sum(int x) {
		x = MAXN-1-x;
		int ans = 0;
		for (; x <= MAXN; x |= x + 1) ans += fen[x];
		return ans;
	}
};



int main(){
	int N,M; scanf("%d %d", &N, &M);
	vector<int> perm(N);
	vector<int> loc(N+1);
	rep(i,N){
		scanf("%d", &perm[i]);
		loc[perm[i]] = i;
	}

	//Node* root = new Node(0,N);
	Fen fen;
	memset(fen.fen,0,sizeof(fen.fen));
	vector<pair<pair<int,int>, pair<int,int> > > events;

	For(i,1,N+1){
		for(int k = i; k <= N; k+= i){
			int a = loc[i], b = loc[k];
			if(a > b)
				swap(a,b);
			events.pb(mp(mp(a,1), mp(b, -1)));
			//root->put(b, 1);
			fen.upd(b, 1);
		}
	}


	rep(i,M){
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		events.pb(mp(mp(a, 0), mp(b,i)));
	}

	sort(events.begin(), events.end());

	vector<int> ans(M);
	foreach(it, events){
		int a = it->F.F, type = it->F.S, b = it->S.F, idx = it->S.S;
		if(type == 0){
			//ans[idx] = root->read(0, b+1);
			ans[idx] = fen.sum(b);
		} else{
			//root->put(b, -1);
			fen.upd(b,-1);
		}
	}

	foreach(it, ans)
		cout << *it << endl;
}	
