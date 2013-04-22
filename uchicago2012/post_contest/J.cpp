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


struct Point3{
	double x,y,z;
	Point3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
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
		double s = len();
		assert(s > 0);
		return Point3(x/s, y/s, z/s);
	}
	Point3 scale(double d){
		return unit().mult(d);
	}
	inline double dot(Point3 in){
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
	vector<double> A;
	vector<double> bias;
	set<set<int> > got;
	rep(a_idx, n) For(b_idx,a_idx+1, n){
		int c_idx;
		for(c_idx = 0; c_idx == a_idx || c_idx == b_idx; c_idx++)
			;
		Point3 a = pts[a_idx], b = pts[b_idx], c = pts[c_idx];
	
		Point3 v1 = b.sub(a).unit();

		Point3 v2 = c.sub(a);
		v2 = v2.sub(v1.scale(v2.dot(v1))).unit();
		assert(abs(v1.dot(v2)) < eps);
		

		double low=0.0, high=0.0;
		int low_idx = -1, high_idx = -1;
		rep(d_idx, n) if(d_idx != a_idx && d_idx != b_idx){
			Point3 d = pts[d_idx];
			Point3 v4 = d.sub(a);
			v4 = v4.sub(v1.scale(v4.dot(v1))).unit();
			assert(abs(v1.dot(v4)) < eps);
			double val = v2.cross(v4).len();
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
			rep(j,2){
				int p3_idx = k ? low_idx : high_idx;
				Point3 p1 = a, p2 = b, p3 = pts[p3_idx];
				if(j)
					swap(p2, p3);

				Point3 vec = p3.sub(p1).cross(p2.sub(p1)).unit();
				double bia = -vec.dot(p1);

				bool bad = false;
				rep(i,n){
					if(pts[i].dot(vec) + bia < -eps)
						bad = true;
				}

				if(!bad){
					set<int> cur;
					cur.insert(a_idx); cur.insert(b_idx); cur.insert(p3_idx);
					if(!got.count(cur)){
						got.insert(cur);
						A.pb(vec.x); A.pb(vec.y); A.pb(vec.z);
						bias.pb(bia);
					}
				}
			}
		}
	}

	int nq; cin>>nq;
	rep(tq, nq){
		double x,y,z; cin>>x>>y>>z;
		double res = 1e10;
		double* ptr1 = &(*A.begin());
		double* ptr2 = &(*bias.begin());
		double* ptr1e = &(*A.end());
		while(ptr1 != ptr1e){
			double a = *ptr1, b = *(ptr1+1), c = *(ptr1+2), bias = *ptr2;
			double hit = x*a + y*b + z*c + bias;
			ptr1 += 3;
			ptr2 += 1;
			res = min(res, hit);
		}
		/*
		for(int i = 0; i < sz(bias); i++){
			double hit = Point3(A[3*i], A[3*i +1], A[3*i+2]).dot(Point3(x,y,z)) + bias[i];
			cout << hit << endl;
			res = min(res, hit);
		}
		*/
		cout << setprecision(4) << fixed << res << endl;
	}
}
}	
