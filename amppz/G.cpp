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

const double eps = 1e-9;
bool EQ(double a, double b){return abs(a - b) < eps;}
double SQ(double d) {return d*d;}

struct Point{
	double x,y;
	Point(double _x, double _y) : x(_x), y(_y){
	}
	Point() {}
	Point add(Point p) {
		return Point(x+p.x, y+p.y);
	}
	Point sub(Point p){
		return Point(x-p.x, y-p.y);
	}
	Point mult(double d){
		return Point(x*d, y*d);
	}
	double dot(Point p){
		return x*p.x + y*p.y;
	}
	double cross(Point p){
		return x*p.y - y*p.x;
	}
	double len() {return hypot(x,y);}
	double dist(Point p) {return sub(p).len();}
	bool operator==(Point p){
		return EQ(dist(p), 0);
	}
};
ostream& operator<<(ostream& out, Point p){
	out << "<" << p.x << ", " << p.y << ">";
	return out;
}
Point null(432145523.154324, 1324512.64352);

double ccw(Point p1, Point p2, Point p3){
	p2.sub(p1).cross(p3.sub(p1));
}

Point v0;
bool convexHullComp(Point a, Point b){
	if(a == v0) return true;
	if(b == v0) return false;
	double hit = ccw(v0, a, b);
	if(EQ(hit, 0))
		return v0.dist(a) < v0.dist(b);
	return hit > 0;
}

vector<Point> convexHull(vector<Point> P){
	v0 = null;
	foreach(p, P)
		if(v0 == null || p->x < v0.x - eps || (EQ(p->x, v0.x) && p->y < v0.y))
			v0 = *p;
	sort(P.begin(), P.end(), convexHullComp);
	vector<Point> ch;
	foreach(p, P){
		while(sz(ch) >= 2 && ccw(ch[sz(ch)-1], ch[sz(ch)-1], *p) <= 0)
			ch.pop_back();
		ch.pb(*p);
	}
	return ch;
}

struct Prefix{
	vector<double> dat;
	Prefix(vector<double> vec){
		dat = vector<double>(sz(vec)+1);
		dat[0] = 0;
		rep(i, sz(vec)){
			dat[i+1] = dat[i] + vec[i];
		}
	}
	double query(int a, int b){
		if(a <= b){
			return dat[b] - dat[a];
		} else{
			return query(0, b) + query(a, sz(dat));
		}
	}

};



int main(){
	int N,M; cin>>N>>M;	
	vector<Point> raw;
	rep(i,N){
		double x,y; cin>>x>>y;
		raw.pb(Point(x,y));
	}
	vector<Point> hull = convexHull(raw);
	Point center(0,0);
	foreach(it, hull)
		center = center.add(*it);
	center = center.mult(1.0/sz(hull));

	cout << center << " " <<  hull << endl;

	vector<double> area;
	rep(i, sz(hull)){
		int next = (i+1)%sz(hull);
		area.pb(abs(hull[i].sub(center).cross(hull[next].sub(center)))/2.0);
	}
	cout << area << endl;
	Prefix pref = Prefix(area);

	cout << pref.query(0, sz(hull)) << endl;
}	
