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

const void setmin(double& a, double b){
	a = min(a,b);
}

#define SQ(x) ((x)*(x))

int main(){
	int n; cin>>n;
	vector<double> XC(2), YC(2), ZC(2);
	rep(i,2)
		cin >> XC[i] >> YC[i] >> ZC[i];
	sort(XC.begin(), XC.end());
	sort(YC.begin(), YC.end());
	sort(ZC.begin(), ZC.end());
	
	vector<double> X(n),Y(n),Z(n);
	rep(i,n)
		cin >> X[i] >> Y[i] >> Z[i];

	vector<int> seed;
	rep(i,n) seed.pb(i);

	double ans = 0.0;
	do{
		double got[n];
		double res = 0;
		rep(i,n)
			got[i] = 0.0;
		rep(cur, n){
			int idx = seed[cur];
			double high = 1e10;	
			if(X[idx] < XC[0] || X[idx] > XC[1]) continue;
			if(Y[idx] < YC[0] || Y[idx] > YC[1]) continue;
			if(Z[idx] < ZC[0] || Z[idx] > ZC[1]) continue;
			rep(k,2){
				setmin(high, abs(XC[k] - X[idx]));
				setmin(high, abs(YC[k] - Y[idx]));
				setmin(high, abs(ZC[k] - Z[idx]));
			}
			rep(i, cur){
				int to = seed[i];
				setmin(high, sqrt(SQ(X[idx] - X[to]) 
							+ SQ(Y[idx] - Y[to]) 
							+ SQ(Z[idx] - Z[to])) - got[to]);
			}
			high = max(0.0, high);
			got[idx] = high;
			res += 4.0/3.0*M_PI*high*high*high;
		}
		ans = max(ans, res);
	}while(next_permutation(seed.begin(), seed.end()));
	
	double area = (XC[1] - XC[0])*(YC[1] - YC[0])*(ZC[1] - ZC[0]);
	cout << ((long long)round(area - ans)) << endl;
}	
