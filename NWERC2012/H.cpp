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

#define TWO(x) (1LL<<(x))

const int MAXP = 71;
vector<int> primes;
const int P = 19;

pair<int,int> getVec(int x){
	int res = 0;
	rep(i, P){
		while((x % primes[i]) == 0){
			res = res ^ TWO(i);
			x /= primes[i];
		}
	}
	return mp(res, x);	
}

typedef __int128_t int128;

long long sqrt(int128 v){
	int128 a = 0;
	int128 b = TWO(62);
	while(a != b){
		int128 m = (a+b)/2;
		if(m*m < v)
			a = m+1;
		else
			b = m;
	}
	assert(a*a == v);
	return (long long) a;
}

int128 dist[TWO(P)];
set<int> path[TWO(P)];

const int MAXN = 5000;

bool safe_mul(int128 a, int128 b){
	return (a*b)/b == a;
}

int main(){
	For(i,2,MAXP){
		bool ok = true;
		For(k,2,i) if((i % k) == 0)
			ok = false;
		if(ok)
			primes.pb(i);
	}
	assert(sz(primes) == P);

	int a,b;
	while(cin >> a >> b){
		map<int, vector<int> > dup;
		vector<int> opts;
		For(at, a, b+1){
			pair<int,int> hit = getVec(at);
			if(hit.S == 1)
				opts.pb(at);
			else {
				assert(hit.S >= 71);
				dup[hit.S].pb(at);
			}
		}
		foreach(it, dup){
			vector<int>& cur = it->S;
			rep(i, sz(cur)) For(k,i+1, sz(cur)){
				opts.pb(cur[i]*cur[k]);
			}
		}

		vector<int> cache(sz(opts));
		rep(i, sz(opts)){
			cache[i] = getVec(opts[i]).F;
		}


		//TODO: not necessary?
		rep(i, TWO(P)){
			path[i].clear();
			dist[i] = -1;
		}

		typedef pair<int128, int> State;
		priority_queue<State,vector<State>, greater<State> > pq;
		rep(i, sz(opts)){
			int sig = cache[i];
			if(dist[sig] == -1 || opts[i] < dist[sig]){
				dist[sig] = opts[i];
				pq.push(mp(opts[i], sig));
				path[sig].clear();
				path[sig].insert(i);
			}
		}
		int128 res = -1;
		while(!pq.empty()){
			int128 num = pq.top().F;
			int sig = pq.top().S;
			pq.pop();
			if(num > dist[sig])
				continue;

			if(res != -1 && num >= res){
				break;
			}
			if(sig == 0){
				res = num;
				break;
			}
			
			set<int> freeze = path[sig];
			rep(i, sz(opts)) if(!freeze.count(i)){
				int to_sig = sig ^ cache[i];
				if(safe_mul(num, opts[i])){
					int128 to_num = num*opts[i];
					if(dist[to_sig] != -1){
						if(safe_mul(to_num, dist[to_sig])){
							if(res == -1 || to_num*dist[to_sig] < res)
								res = to_num*dist[to_sig];
						}
					}
					if(dist[to_sig] == -1 || to_num < dist[to_sig]){
						dist[to_sig] = to_num;
						pq.push(mp(to_num, to_sig));

						path[to_sig] = freeze;
						path[to_sig].insert(i);
					}
				}
			}
		}
		if(res == -1)
			cout << "none" << endl;
		else
			cout << sqrt(res) << endl;

	}
	
}	
