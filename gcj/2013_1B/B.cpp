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

int getNum(int shell){
	int base = shell*2 + 1;
	return (base*(base+1))/2;
}


const int MAXN = 2000;
	

int main(){
int cases; cin>>cases;

rep(cas, cases){
	int N, X, Y; cin>>N>>X>>Y;
	int shell = (abs(X) + Y)/2;
	int num_shell = getNum(shell);
	int last_shell = getNum(shell-1);
	double res = 424242;
	if(N <= last_shell){
		res = 0.0;
	}
	else if(N >= num_shell){
		res = 1.0;
	} else{
		int exc = N - last_shell;
		int shell_height = shell*2 + 1;
		assert(exc < (shell_height*2-1));
		int need = Y + 1;
		if(need == shell_height){
			res = 0.0;
		} else{
			//cout << X << " " << Y << " " << shell_height << endl;
			assert(shell_height < MAXN);
			assert(need < MAXN);
			vector<vector<double> > DP(MAXN, vector<double>(MAXN, 0.0));
			DP[0][0] = 1.0;
			rep(i, shell_height) rep(k, shell_height){
				int tot = i + k;
				if(tot >= exc)
					continue;
				if(i == shell_height-1 && k == shell_height-1){
					assert(0);
				} if(i == shell_height-1){
					DP[i][k+1] += DP[i][k];
				} else if(k == shell_height-1){
					DP[i+1][k] += DP[i][k];
				} else{
					DP[i+1][k] += 0.5*DP[i][k];
					DP[i][k+1] += 0.5*DP[i][k];
				}
			}

			res = 0.0;
			//res = DP[need][exc-need];
			For(i, need, shell_height){
				if(exc - i >= 0 /*&& exc-i < shell_height*/){
					res += DP[i][exc-i];
				}
			}
			
		}
	}
	printf("Case #%d: ", cas+1);
	cout << fixed << setprecision(10) << res << endl;

}
}	
