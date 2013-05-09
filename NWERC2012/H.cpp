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

int128 dp[TWO(P)];
int128 n_dp[TWO(P)];

const int MAXN = 5000;

int main(){
	For(i,2,MAXP){
		bool ok = true;
		For(k,2,i) if((i % k) == 0)
			ok = false;
		if(ok)
			primes.pb(i);
	}
	cout << primes << endl;
	assert(sz(primes) == P);

	int a,b;
	while(cin >> a >> b){
		int small_square = -1;
		for(int i = 5000; i>= 1; i--){
			int hit = i*i;
			if(hit >= a && hit <= b)
				small_square = hit;
		}

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
				cout << cur[i] << " " << cur[k] << endl;
			}
		}
		
		sort(opts.begin(), opts.end());

		memset(dp,-1,sizeof(dp));
		foreach(it, opts){
			int& at = *it;

			if(small_square != -1 && at >= small_square)
				break;

			int sig = getVec(at).F;
			
			memcpy(n_dp, dp, sizeof(dp));

			for(int i = TWO(P)-1; i >= 1; i--) if(dp[i] >= 0){
				assert(dp[i] > 1);
				int next = i ^ sig;
				if(n_dp[next] == -1 || (dp[i]*at) < n_dp[next]){
					n_dp[next] = dp[i]*at;
				}
			}
			if(n_dp[sig] == -1 || at < n_dp[sig]){
				n_dp[sig] = at;
			}

			memcpy(dp, n_dp, sizeof(dp));
		}

		int128 res = -1;
		if(small_square != -1)
			res = small_square;
		if(dp[0] != -1){
			if(res == -1 || dp[0] < res)
				res = dp[0];
		}

		cout << getVec(3976) << " " << getVec(4047) << endl;
		int sig = getVec(3976).F ^ getVec(4047).F;
		cout << sig << endl;
		assert(dp[sig] >= 0);
		cout << sqrt(dp[sig]*3976*4047) << endl;

		//cout << "HEY: " << (long long)dp[0] << endl;
		//cout << small_square << endl;
		if(res == -1)
			cout << "none" << endl;
		else
			cout << sqrt(res) << endl;
	}
	
}	
