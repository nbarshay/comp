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
#define X first
#define Y second

vector<pair<double,double> > lower, upper;
int w,nl,nu,g;

double cross(pair<double,double> a, pair<double,double> b){
	return a.X*b.Y - a.Y*b.X;
}
pair<double,double> sub(pair<double,double> a, pair<double,double> b){
	return mp(a.X - b.X, a.Y - b.Y);
}

double query(double x){
	vector<pair<double,double> > a,b;
	rep(i, nl){
		a.pb(lower[i]);
		if(lower[i+1].X >= x){
			double alpha = (x - lower[i].X) / (lower[i+1].X - lower[i].X);
			double ya = lower[i+1].Y * alpha + lower[i].Y * (1-alpha);
			a.pb(mp(x, ya));
			break;
		}
	}
	rep(i, nu){
		b.pb(upper[i]);
		if(upper[i+1].X >= x){
			double alpha = (x - upper[i].X) / (upper[i+1].X - upper[i].X);
			double yb = upper[i+1].Y * alpha + upper[i].Y*(1-alpha);
			b.pb(mp(x,yb));
			break;
		}
	}
	vector<pair<double,double> > final;
	rep(i, sz(a))
		final.pb(a[i]);
	for(int i = sz(b)-1; i>= 0; i--)
		final.pb(b[i]);
	double ans = 0;
	For(i,1,sz(final)-1){
		ans += cross(sub(final[i], final[0]), sub(final[i+1], final[0]));
	}
	return abs(ans)/2.0;
}

int main(){
int np; cin>>np;
rep(tp,np){
	cin >> w >> nl >> nu >> g;
	lower.clear();
	upper.clear();
	rep(i, nl){
		double x,y; cin>>x>>y;
		lower.pb(mp(x,y));
	}
	rep(i, nu){
		double x,y; cin>>x>>y;
		upper.pb(mp(x,y));
	}
	double area = query(w);
	printf("Case #%d:\n", tp+1);
	For(iter,1, g){
		double target = (area / double(g))*double(iter);
		double a = 0, b = w;
		while(abs(a-b) > 1e-9){
			double m = (a+b)/2.0;
			double hit = query(m);
			if(hit > target)
				b = m;
			else
				a = m;
		}
		cout << setprecision(8) << fixed << (a+b)/2 << endl;
	}
}
}	
