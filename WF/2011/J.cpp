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

const int MAXN = 1000005;
int dp[MAXN];
int back[MAXN];	//index into opt

int waste[MAXN][300];

int main(){
	memset(waste,0,sizeof(waste));
	vector<pair<int, pair<char,int> > > opt;
	int area = 0;
	for(int i = 1; ; i++){
		area += i*i;
		if(area >= MAXN)
			break;

		if(i >= 2)
			opt.pb(mp(area, mp('H', i)));
	}

	area = 0;
	for(int i = 1; ; i+=2){
		area += i*i;
		if(area >= MAXN)
			break;

		if(i >= 3)
			opt.pb(mp(area, mp('L', i)));
	}

	area = 0;
	for(int i = 2; ; i+=2){
		area += i*i;
		if(area >= MAXN)
			break;

		if(i >= 3)
			opt.pb(mp(area, mp('L', i)));
	}
	sort(opt.begin(), opt.end());

	memset(dp,0x04f,sizeof(dp));
	dp[0] = 0;
	rep(cur, sz(opt)){
		int step = opt[cur].F;
		for(int i = MAXN-1; i>=0; i--){
			int to = i+step;
			if(to < MAXN){
				int val = dp[i] + 1;
				if(val <= dp[to]){
					dp[to] = val;
					back[to] = cur;
				}
			}
		}
	}

	int cas=0;
	while(1){
		int N; cin>>N;
		if(N==0)
			break;
		printf("Case %d:", ++cas);
		if(dp[N] > 1000){
			printf(" impossible\n");
			continue;
		}
		
		int at = N;
		while(at != 0){
			pair<char,int> sig = opt[back[at]].S;
			printf(" %d%c", sig.S, sig.F);
			at -= opt[back[at]].F;
		}
		printf("\n");
	}


}	
