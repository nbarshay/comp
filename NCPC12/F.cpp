#include <iostream>
#include <string>
#include <unordered_map>
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

typedef long long ll;

namespace std{
	template <>
	struct hash<std::pair<ll, int> > {
	public:
			size_t operator()(std::pair<ll, int> x) const throw() {
				 size_t h = x.F ^ x.S; 
				 return h;
			}
	};
}



#define MAXN 13
ll pow13[MAXN];

int get(ll& x, int idx){
	return (x / pow13[idx]) % MAXN;
}

int union_set(ll& x, int idx, int val){
	x += val*pow13[idx];
}


void fix(ll& x){
	int cnt = 0;	
	int lookup[MAXN];
	memset(lookup, -1, sizeof(lookup));
	ll res = 0;
	rep(i, MAXN){
		int hit = get(x, i);
		if(lookup[hit] == -1)
			lookup[hit] = cnt++;
		union_set(res, i, lookup[hit]);
	}
	x = res;
}

void merge(ll& x, int a, int b){
	int sa = get(x,a);	
	int sb = get(x,b);
	ll res = 0;
	rep(i, MAXN){
		int hit = get(x, i);
		if(hit == sb)
			hit = sa;
		union_set(res, i, hit);
	}
	x = res;
	fix(x);
}

void clean(ll& s, set<int>& special){
	ll res = 0;
	rep(i, MAXN) if(special.count(i))
		union_set(res, i, get(s, i));
	s = res;
	fix(s);
}

#define TWO(x) (1<<(x))

void addEdge(int& s, int a, int b){
	s = s ^ TWO(a);
	s = s ^ TWO(b);
}

const int inf = 1000000000;


int main(){

pow13[0] = 1;
For(i,1,MAXN)
	pow13[i] = pow13[i-1]*MAXN;


int N,R;
while(cin >> N >> R){
	int base_cost = 0;

	ll base = 0;
	rep(i,MAXN)
		union_set(base, i, i);

	vector<vector<int>> cost(N, vector<int>(N,inf));
	int base_par = 0;
	set<int> special;
	special.insert(0);

	rep(i,R){
		int a,b,c; cin>>a>>b>>c;
		a--; b--;

		special.insert(a); special.insert(b);

		merge(base, a, b);

		base_cost += c;
		addEdge(base_par, a, b);
		cost[a][b] = min(cost[a][b], c);
		cost[b][a] = min(cost[b][a], c);
	}

	clean(base, special);

	int M; cin>>M;
	rep(iter,M){
		int a,b,c; cin>>a>>b>>c;	
		a--; b--;
		cost[a][b] = min(cost[a][b], c);
		cost[b][a] = min(cost[b][a], c);
	}

	rep(j,N) rep(i,N) rep(k,N)
		cost[i][k] = min(cost[i][k], cost[i][j] + cost[j][k]);

	unordered_map<pair<ll, int>, int> dp;
	dp[mp(base,base_par)] = 0;
		
	for(int a : special) for(int b : special) if(a<b) if(cost[a][b] < inf){
		unordered_map<pair<ll, int>, int> n_dp = dp;
		for(const auto& at : dp){
			ll next_s = at.F.F;
			merge(next_s, a, b);
			rep(k,2){
				int next_p = at.F.S;
				if(k)
					addEdge(next_p, a, b);

				auto hit = mp(next_s, next_p);
				int val = at.S + cost[a][b] * (k ? 1 : 2);
				auto it = n_dp.find(hit);
				if(it == n_dp.end()){
					n_dp[hit] = val;	
				} else{
					it->S = min(it->S, val);
				}
			}
		}
		dp = n_dp;
	}

	assert(dp.count(mp(0, 0)));
	cout << dp[mp(0,0)] + base_cost << endl;
}
}
