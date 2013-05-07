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

void setmin(map<int,int>& m, int idx, int v){
	if(m.count(idx))
		m[idx] = min(m[idx], v);
	else
		m[idx] = v;
}

int solve3(vector<int>& a, vector<int>& b){
	int n = sz(a);
	vector<int> P(n+1);
	rep(i,n)
		P[b[i]] = i;
	map<int,int> cost;
	cost[0]= 0;
	rep(i,n){
		int delta = i - P[a[i]];
		if(cost.count(delta)){
			setmin(cost, delta+1, cost[delta] + 1);
			setmin(cost, delta-1, cost[delta]);
			cost.erase(delta);
		}
	}
	int res = -1;
	foreach(it, cost){
		int base = it->S, delta= it->F;
		//printf("%d %d\n", base, delta);
		int hit;
		if(delta < 0)
			hit = base + -delta;
		else
			hit = base;
		if(res == -1 || hit < res)
			res = hit;
	}
	//cout << "RES: " << res << endl;
	return res + sz(a);
}

int solve(vector<int>& a, vector<int>& b){
	int n = sz(a);
	int loca = 0, locb = 0;
	bool quant = false;
	int cost = 0;
	while(loca != n || locb != n){
		//printf("%d %d %d %d\n", loca, locb, quant, cost);

		cost++;
		if(loca == n){
			if(quant){
				quant = false;
				cost--;
			}
			locb++;
		} else if(locb == n){
			if(quant){
				quant = false;
				cost--;
			}
			loca++;
		} else{
			if(!quant){
				if(a[loca] == b[locb]){
					loca++;
					locb++;
					quant = true;
					cost++;
				} else{
					loca++;
					locb++;
				}
			}
			else{
				bool conda = loca + 1 < n && a[loca+1] == b[locb];
				bool condb = locb + 1 < n && b[locb+1] == a[loca];
				if(conda && condb){
					/*if(loca == locb)
						cost++;*/
					loca++;
					locb++;
					cost++;
				}
				if(conda){
					quant = false;
					locb++;
					cost--;
				} else if(condb){
					quant = false;
					loca++;
					cost--;
				} else{
					loca++;
					locb++;
				}
			}
		}
	}
	return cost;
}

int solve2(vector<int>& a, vector<int>& b){
	int n = sz(a);
	int mem[105][105];
	memset(mem,0x4f, sizeof(mem));
	mem[0][0] = 0;
	rep(i, n+1) rep(k,n+1){
		if(i < n && k < n && a[i] != b[k]){
			mem[i+1][k+1] = min(mem[i+1][k+1], mem[i][k] + 1);
		} 
		mem[i][k+1] = min(mem[i][k+1], mem[i][k] + 1);
		mem[i+1][k] = min(mem[i+1][k], mem[i][k] + 1);
	}
	return mem[n][n];
}

void test(){
	vector<int> a, b;
	rep(i,10){
		a.pb(i);
		b.pb(i);	
	}
	random_shuffle(a.begin(), a.end());
	random_shuffle(b.begin(), b.end());
	int hita = solve2(a,b);
	int hitb = solve3(a,b);
	if(hita != hitb)
		cout << a << " " << b << " " << hita << " " << hitb << endl;
}


int main(){
	/*
	rep(i,10000)
		test();
	return 0;
	*/

	//while(1){
			int n; cin>>n;
			vector<int> a(n), b(n);
			rep(i,n) cin>>a[i];
			rep(i,n) cin>>b[i];
			cout << solve3(a,b) << endl;
	//}
}	
