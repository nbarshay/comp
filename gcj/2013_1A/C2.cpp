#include <iostream>
#include <unordered_map>
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

const int TWO(int x){ return 1<<x; }

const int N = 12, M = 8, K = 12;

vector<int> gen(){
	vector<int> res;
	rep(i, N){
		res.pb((rand() % 7) + 2);
	}
	return res;
}

vector<int> proc(vector<int> card){
	vector<int> res;
	rep(i, K){
		int seed = rand() % TWO(N);
		int prod = 1;
		rep(k, N) if(seed & TWO(k))
			prod *= card[k];
		res.pb(prod);
	}
	return res;
}

bool guess(vector<int> V){
	int pow5 = 0, pow7 = 0;
	for(int c : V){
		int t = 0;
		while((c % 5) == 0){
			t++;
			c/=5;
		}
		pow5 = max(pow5, t);
	}
	for(int c : V){
		int t = 0;
		while((c % 7) == 0){
			t++;
			c/=7;
		}
		pow7 = max(pow7, t);
	}
	return pow5 + pow7 >= 2;
}

vector<vector<int> > opt;
vector<unordered_map<int,double> > V;
vector<double> bias;

double fact(int n){
	if(n==0) return 1.0;
	else return n*fact(n-1);
}

double choose(int n, int k){
	return fact(n)/(fact(n-k)*fact(k));
}

double getBias(vector<int>& V){
	vector<int> freq(9);
	for(int x : V)
		freq[x]++;
	int rem = 12;
	double res = 1.0;
	for(int x : freq) if(x > 0){
		res *= choose(rem, x);
		rem -= x;
	}
	return res;
}

void rec(int at, vector<int> cur){
	if(sz(cur) == 12){
		opt.pb(cur);
		return;
	}
	for(int i = at; i <= 8; i++){
		vector<int> copy = cur;
		copy.pb(i);
		rec(i, copy);
	}
}

vector<int> solve(vector<int> dat){
	int best = -1;
	double best_prob = -1.0;
	rep(i, sz(opt)){
		double prob = bias[i];
		for(int& c : dat){
			prob *= V[i][c];
			if(prob < best_prob)
				break; 
		}
		if(prob > best_prob){
			best_prob = prob;
			best = i;
		}
	}
	return opt[best];
}

int main(){
	rand();
	rec(2, vector<int>());	
	V = vector<unordered_map<int, double> >(sz(opt));
	rep(i, sz(opt)){
		vector<int>& cur = opt[i];
		rep(seed, TWO(N)){
			int prod = 1;
			rep(k, N) if(seed & TWO(k))
				prod *= cur[k];
			V[i][prod] += double(1.0)/double(TWO(N));
		}
	}

	bias = vector<double>(sz(opt));
	rep(i, sz(opt)){
		bias[i] = getBias(opt[i]);
	}

	cerr << "READY: " << endl;

	int np; cin>>np;
	printf("Case #1:\n");
	int r,n,m,k; cin>>r>>n>>m>>k;
	assert(n == 12 && m == 8 && k == 12);
	rep(i,r){
		vector<int> bla(k);
		rep(i, k){
			long long t; cin>>t;
			bla[i] = (int)t;
		}
		vector<int> res = solve(bla);
		for(int c : res)
			cout << c;
		cout << endl;
	}

	/*
	int n = 500;
	int bad = 0;
	rep(i,n){
		vector<int> card = gen();
		sort(card.begin(), card.end());
		vector<int> c2 = solve(proc(card));
		if(card != c2)
			bad++;
	}
	cout << bad << "/" << n << endl;
	*/

}	
