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

struct Point3;
ostream& operator<<(ostream& out, const Point3& p);

struct Point3{
	double x,y,z;
	Point3(double _x, double _y, double _z) : x(_x), y(_x), z(_z) {}
	Point3 add(Point3 in){
		return Point3(x + in.x, y + in.y, z + in.z);
	}
	Point3 sub(Point3 in){
		return Point3(x - in.x, y - in.y, z - in.z);
	}
	Point3 mult(double d){
		return Point3(x*d, y*d, z*d);
	}
	double len(){
		return sqrt(x*x + y*y + z*z);
	}
	Point3 unit(){
		cout << (*this) << endl;
		double s = len();
		assert(s > 0);
		return Point3(x/s, y/s, z/s);
	}
	Point3 scale(double d){
		return unit().mult(d);
	}
	double dot(Point3 in){
		return x*in.x + y*in.y + z*in.z;
	}
	Point3 cross(Point3 in){
		return Point3(y*in.z - z*in.y,z*in.x - x*in.z, x*in.y - y*in.x);
	}
};

ostream& operator<<(ostream& out, const Point3& p){
	out << "[" << p.x << ", " << p.y << ", " << p.z << "]";
	return out;
}

const double eps = 1e-9;


int main(){
while(1){
	int n; cin>>n;
	if(n==0)
		break;
	vector<Point3> pts;
	rep(i,n){
		double x,y,z; cin>>x>>y>>z;
		pts.pb(Point3(x,y,z));
	}
	vector<Point3> planes;
	vector<double> bias;
	rep(a_idx, n) For(b_idx,a_idx+1, n){
		int c_idx;
		for(c_idx = 0; c_idx == a_idx || c_idx == b_idx; c_idx++)
			;
		printf("%d %d %d\n", a_idx, b_idx, c_idx);
		Point3 a = pts[a_idx], b = pts[b_idx], c = pts[c_idx];
	
		Point3 v1 = b.sub(a).unit();

		Point3 v2 = c.sub(a);
		cout << v2 << v1.scale(v2.dot(v1)) << endl;
		v2 = v2.sub(v1.scale(v2.dot(v1))).unit();
		assert(abs(v1.dot(v2)) < eps);
		
		Point3 v3 = v1.cross(v2);
		assert(abs(v3.len() - 1.0) < eps);

		double low=0.0, high=0.0;
		int low_idx = -1, high_idx = -1;
		rep(d_idx, n) if(d_idx != a_idx && d_idx != b_idx){
			Point3 d = pts[d_idx];
			Point3 v4 = d.sub(a);
			v4 = v1.sub(v3.scale(v3.dot(v1))).unit();
			assert(abs(v1.dot(v3)) < eps);
			double val = v3.cross(v4).len();
			if(val <= low){
				low = val;
				low_idx = d_idx;
			}
			if(val >= high){
				high = val;
				high_idx = d_idx;
			}
		}
		assert(low_idx != -1 && high_idx != -1);
		rep(k,2){
			Point3 p1 = a, p2 = b, p3 = k ? pts[low_idx] : pts[high_idx];
			Point3 vec = p3.sub(p1).cross(p2.sub(p1)).unit();

			planes.pb(vec);
			bias.pb(-vec.dot(p1));
		}
	}
	int nq; cin>>nq;
	rep(tq, nq){
		double x,y,z; cin>>x>>y>>z;
		Point3 q = Point3(x,y,z);
		double res = 1e10;
		rep(k, sz(planes)){
			double hit = abs(planes[k].dot(q) - bias[k]);
			res = min(res, hit);
		}
		cout << setprecision(4) << fixed << res << endl;
	}
}
}	
