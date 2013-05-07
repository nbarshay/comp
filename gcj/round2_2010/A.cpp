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

#define SQ(x) ((x)*(x))

vector<vector<int>> A;
int n;

bool check(int i, int k, int ii, int kk){
	if(ii < 0 || ii >= n || kk < 0 || kk >= n)
		return true;
	if(i < 0 || i >= n || k < 0 | k >= n)
		return true;
	return A[i][k] == A[ii][kk];
}

int main(){
int cases; cin>>cases;
rep(cas, cases){
	cin>>n;
	A = vector<vector<int>>(n, vector<int>(n));
	for(int i = 1; i <= n; i++){
		rep(k, i){
			cin >>A[i-1-k][k];
		}
	}
	for(int i = n-1; i>=1; i--){
		rep(k, i){
			cin >> A[n-1-k][n-1-i + 1 + k];
		}
	}

	int best = 1000000000;
	
	For(r, -2*n, 4*n+1) For(c, -2*n, 4*n+1){
		if((r % 2) != (c % 2))
			continue;

		//printf("BLA: %d %d\n", r,c);
		bool ok = true;
		for(int i = -4*n; i <= 4*n; i++) for(int k = -4*n; k <= 4*n; k++){

			int r1=  r - i - k;
			int c1 = c + k - i;
			int r2 = r + i - k;
			int c2 = c + k + i;
			int r3 = r - i + k;
			int c3 = c - k - i;

			if(((r1%2) == 0) || ((c1 % 2) == 0))
				continue;
			if(!check((r1-1)/2,(c1-1)/2,(r2-1)/2,(c2-1)/2))
				ok = false;
			if(!check((r1-1)/2,(c1-1)/2,(r3-1)/2,(c3-1)/2))
				ok = false;

		}
		if(ok){
			int hit = SQ(max(abs(r - n),abs(c-n)) + n) - SQ(n);
			best = min(best, hit);
		}


	}
	printf("Case #%d: %d\n", cas+1, best);


}
}	
