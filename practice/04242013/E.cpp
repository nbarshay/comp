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

const int PLUS = 0;
const int MINUS = 1;
const int TIMES = 2;
const int DIV = 3;
const int EQ = 4;

const int ST_S = 0;
const int ST_O = 1;
const int ST_N = 2;

struct State{
	int st;
	int op;
	int disp;
	int value;
	bool operator<(const State& in) const{
		return make_tuple(st,op,disp,value) < 
			make_tuple(in.st, in.op, in.disp, in.value);
	}

	void calc(){
		switch(op){
			case PLUS: disp = value + disp; break;
			case TIMES: disp = value * disp; break;
			case MINUS: disp = value - disp; break;
			case DIV: 
				disp = (disp == 0) ? -1 : (value / disp);
				break;
			default:
				assert(0);
				break;
		}
	}

	bool evolve(char com){
		int type;
		int val;
		switch(com){
			case '+': type=0; val=PLUS; break;
			case '-': type=0; val=MINUS; break;
			case '*': type=0; val=TIMES; break;
			case '/': type=0; val=DIV; break;
			case '=': type=0; val=EQ; break;
			default: type=1; val=com-'0'; break;
		}
		if(st == ST_S){
			if(type == 0){
				st = ST_O;
				op = val;
			} else{
				st = ST_N;
				disp = val;
			}
		} else if(st == ST_O){
			if(type == 0){
				if(val == EQ && op != EQ)
					calc();
				op = val;
				value = disp;
			} else{
				disp = val;
				st = ST_N;
			}
		} else if(st == ST_N){
			if(type == 0){
				if(op != EQ && op != -1)
					calc();
				op = val;
				value = disp;
				st = ST_O;
			} else{
				disp = 10*disp + val;
			}
		}

		return disp >= 0 && disp <= 999;
	}
};

ostream& operator<<(ostream& out, State st){
	out << "(" << st.st <<" " << st.op << " " << st.disp << " " << st.value << ")";
	return out;
}


int main(){
string B; 
int goal;
while(cin >> B >> goal){
	map<State,int> D;
	queue<State> q;
	State start; start.st = ST_S; start.op = -1; start.value = start.disp = 0;
	D[start] = 0;
	q.push(start);
	int best = -1;
	while(!q.empty()){
		State top = q.front();
		q.pop();
		if(top.disp == goal){
			best = D[top];
			break;
		}
		for(char com : B){
			State next = top;
			if(next.evolve(com)){
				if(!D.count(next)){
					D[next] = D[top] + 1;
					q.push(next);
				}
			}
		}
	}
	if(best >= 0)
		cout << best << endl;
	else
		cout << "impossible" << endl;
}
}	
