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

#define PI M_PI

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

const double eps = 1e-9;
bool EQ(double a, double b){return abs(a-b) < eps;}
double SQ(double d){return d*d;}

template<class T>
vector<T> makeVec(T a, T b){
	vector<T> ans(2);
	ans[0] = a, ans[1] = b;
	return ans;
}

double angmod(double a){
	return fmod((fmod(a, 2*M_PI) + 2*M_PI), 2*M_PI);
}


struct Point{
	double x, y;
	Point(double tx, double ty) : x(tx), y(ty) {}
	Point() {}
	Point add(Point p) {return Point(x+p.x, y+p.y);}
	Point sub(Point p) {return Point(x-p.x, y-p.y);}
	Point mult(double d) {return Point(x*d, y*d);}
	double dot(Point p) {return x*p.x+ y*p.y;}
	double cross(Point p) {return x*p.y - y*p.x;}
	double len() {return hypot(x, y);}
	Point scale(double d) {return mult(d/len());}
	double dist(Point p) {return sub(p).len();}
	double ang(){return angmod(atan2(y, x));}
	static Point polar(double r, double theta) {return Point(r*cos(theta), r*sin(theta));}
	Point rot(double theta) {return Point(x*cos(theta)-y*sin(theta), x*sin(theta)+y*cos(theta));}
	Point perp() {return Point(-y, x);}
	bool operator==(const Point& p) {return abs(dist(p)) < eps;}
	double norm() {return dot(*this);}
};
ostream& operator<<(ostream& out, Point p){
	out << "(" << setprecision(8) << p.x << ", " << p.y << ")";
	return out;
}

Point null(2093841.129801, 42390841.21948021);
struct Line{
	Point a, b, along; //along only used by upperhull
	Line(Point ta, Point tb) : a(ta), b(tb) {}
};
double ccw(Point p1, Point p2, Point p3){ //left is 1, right is -1
	return p2.sub(p1).cross(p3.sub(p1));
}


Point lineline(Line a, Line b){
	double d = a.b.sub(a.a).cross(b.b.sub(b.a));
	if(EQ(d, 0))
		return null;
	return a.a.add((a.b.sub(a.a)).mult(b.b.sub(b.a).cross(a.a.sub(b.a))/d));
}

Point pointline(Point p, Line l){
	Point v = l.b.sub(l.a).scale(1);
	double dot = p.sub(l.a).dot(v);
	return l.a.add(v.mult(dot));
}


ostream& operator<<(ostream& out, Line line){
	out << "[" << line.a << "-->" << line.b << "]";
	return out;
}

struct Circle{
	Point p;double r;
	Circle(Point tp, double tr) : p(tp), r(tr) {}
	Circle(Point a, Point b, Point c){
		Point p1 = a.add(b).mult(0.5);
		Line l1 = Line(p1, p1.add(a.sub(b).perp()));
		Point p2 = b.add(c).mult(0.5);
		Line l2 = Line(p2, p2.add(b.sub(c).perp()));
		p = lineline(l1, l2);
		assert(!(p == null));
		r = p.dist(a);
	}
};
ostream& operator<<(ostream& out, Circle circ){
	out << "<" << circ.p << ": " << circ.r << ">";
	return out;
}


//circle
vector<Point> circline(Circle c, Line l){//tested
	Point x = pointline(c.p, l);
	double d = x.dist(c.p);
	if(d > c.r + eps) return vector<Point>();
	double h = sqrt(max(0.0, SQ(c.r) - SQ(d)));
	Point perp = l.a.sub(l.b);
	return makeVec(x.add(perp.scale(h)), x.add(perp.scale(-h)));
}
vector<Line> circcirctan(Circle a, Circle b){//tested
	if(a.r < b.r)
		return circcirctan(b, a);

	vector<Line> res;

	if((a.p.sub(b.p)).len() <= a.r + b.r + eps){
		Point v = b.p.sub(a.p).scale(a.r);
		res.pb(Line(v.add(a.p), v.scale(1.0).rot(M_PI/2.0).add(v.add(a.p))));
	} else{
		double d = a.p.dist(b.p);
		double d1 = a.r*d/(a.r + b.r);
		double t = acos(a.r/d1);
		Point v = b.p.sub(a.p);//crossing
		res.pb(Line(a.p.add(v.scale(a.r).rot(t)), b.p.add(v.scale(-b.r).rot(t))));
		res.pb(Line(a.p.add(v.scale(a.r).rot(-t)), b.p.add(v.scale(-b.r).rot(-t))));
		t = asin((a.r-b.r)/d)+PI/2;
		v = a.p.sub(b.p);//same side
		//res.pb(Line(a.p.add(v.scale(a.r).rot(t)), b.p.add(v.scale(b.r).rot(t))));
		//res.pb(Line(a.p.add(v.scale(a.r).rot(-t)), b.p.add(v.scale(b.r).rot(-t))));
	}
	return res;
}

double angdiff(double a, double b){
	double res = angmod(a-b);
	return min(res, 2*M_PI - res);
}

int main(){
while(1){
	int n; double plat_r, red_x, red_y, red_r;
	cin >> n >> plat_r >> red_x >> red_y >> red_r;	
	if(n==0)
		break;
	Circle platform(Point(0,0), plat_r);
	Circle red(Point(red_x, red_y), red_r);

	vector<pair<double,pair<int, int> > > events;	
	rep(i,n){
		double garb_x, garb_y, garb_r;
		cin >> garb_x >> garb_y >> garb_r;
		Circle cur(Point(garb_x, garb_y), garb_r);
		vector<Line> lines = circcirctan(red, cur);
		vector<Point> res;
		//cout << "HERE: " << lines << endl;

		rep(j,sz(lines)){
			vector<Point> hit = circline(platform, lines[j]);
			//cout << hit << endl;
			assert(sz(hit) == 2);
			int got = 0;
			rep(k,2){
				Point center = cur.p.sub(red.p).scale(red.r).add(red.p);
				Point v1 = hit[k].sub(center);
				Point v2 = cur.p.sub(center);
				if(v1.dot(v2) >= 0){
					res.pb(hit[k]);
					got++;
				}
			}
		}
		//cout << sz(res) << endl;
		assert(sz(res) == 2);	
		Point p1 = res[0], p2 = res[1];

		if(ccw(red.p, p1, p2) < 0)
			swap(p1, p2);
		events.pb(mp(p1.ang(), mp(0, i)));
		events.pb(mp(p1.ang() - 2*M_PI, mp(0,i)));
		events.pb(mp(p2.ang(), mp(1, i)));
		events.pb(mp(p2.ang() - 2*M_PI, mp(1, i)));
	}
	sort(events.begin(), events.end());
	//cout << events << endl;
	double last = 0.0;
	double res = 0.0;
	set<int> cur;
	foreach(it, events){
		double ang = it->F;
		if(ang >= 0 && sz(cur) == 0){
			res += (ang - last);
		}
		if(it->S.F == 0)
			cur.insert(it->S.S);
		else
			cur.erase(it->S.S);
		last = max(0.0, ang);	
	}
	if(sz(cur) == 0){
		res += 2*M_PI - last;
	}

	cout << setprecision(4) << fixed << (res / (2*M_PI)) << endl;
}
}	
