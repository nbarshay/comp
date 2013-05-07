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

int main(){
	int N; cin>>N;
	vector<int> A(2*N-1);
	rep(i, 2*N-1)
		cin >> A[i];
	if(N % 2){
		int res = 0;
		rep(i, sz(A))
			res += abs(A[i]);
		cout << res << endl;
	} else{
		sort(A.begin(), A.end());
		int neg = 0;
		rep(i, sz(A))
			if(A[i] < 0)
				neg++;
		int ans = -1000000000;
		rep(k,2){
			vector<int> B = A;
			bool bad = false;
			if(k){
				rep(i, (neg/2)*2)
					B[i] = -B[i];
			} else{
				rep(i, ((neg+1)/2)*2){
					if(i < sz(A))
						B[i] = -B[i];
					else
						bad = true;
				}
			}
			if(!bad){
				int res = 0;	
				rep(i, sz(A))
					res += B[i];
				ans = max(ans, res);
			}
		}
		cout << ans << endl;
	}
}	
