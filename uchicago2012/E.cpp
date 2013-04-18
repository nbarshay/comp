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

const int MAXN = 2010;
const int MAXK = 30;

int n,m;
int dat[MAXN];

vector<vector<int> > cost;

void compute(int base, vector<int>& res){
	set<pair<int,int> > s;
	set<pair<int,int> >::iterator it = s.end();
	int loc = 0;
	int acc = 0;
	res[base] = acc;
	For(i,base,n){
		pair<int,int> cur = mp(dat[i], i);
		s.insert(cur);
		if(it == s.end()){
			it = s.begin();
		} else{
			int oldval = it->F;
			acc += abs(cur.F - oldval);

			if(cur < *it)
				loc++;

			if((sz(s) % 2) == 0){
				if(cur < *it){

					--it;
					acc += (sz(s) - loc - 1)*(oldval - it->F);
					acc -= (loc - 1)*(oldval - it->F);

					loc--;
					
				} 
			} else{
				if(cur > *it){
					++it;
					acc -= (sz(s) - (loc + 1) -1 ) * (it->F - oldval);
					acc += (loc) * (it->F - oldval);

					loc++;
				} 
			}
		}
		res[i+1] = acc;
	}
}

const int inf = 1000000000;

int DP[MAXN][MAXK];
int dp(int at, int used){
	if(at == 0)
		return 0;
	if(used == 0)
		return inf;

	int& res = DP[at][used];
	if(res >= 0)
		return res;
	res = inf;

	rep(i, at){
		res = min(res, dp(i, used-1) + cost[i][at]);	
	}

	return res;
}

int main(){
while(1){
	cin >> n >> m;
	if(n==0)
		break;
	rep(i,n)
		cin >> dat[i];

	cost = vector<vector<int> >(n, vector<int>(n+1));
	rep(i,n)
		compute(i, cost[i]);

	memset(DP,-1,sizeof(DP));
	cout << dp(n,m) << endl;
}
}	
