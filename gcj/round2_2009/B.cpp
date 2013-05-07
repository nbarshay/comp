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

const int inf = 1000000000;

#define MAXN 55
//row, column, left extent, right extend
int DP[MAXN][MAXN][MAXN][MAXN];

vector<string> grid;
int n,m,f;

bool isBlocked(int r, int c){
	if(r < 0 || c < 0 || r >= n || c >= m)
		return true;
	else
		return grid[r][c] == '#';
}

int getFall(int r, int c){
	int fall = 0;	
	while(!isBlocked(r + fall + 1,c))
		fall++;
	return fall;
}


int rec(int r, int c, int a, int b);

int descTo(int r, int c, int a, int b){
	if(c >= m || c < 0 || a < 0 || b >= m)
		return inf;
	if(getFall(r,c) + 1 > f)
		return inf;
	return rec(r,c,a,b);
}

int rec(int r, int c, int a, int b){
	int& res = DP[r][c][a][b];
	if(res >= 0)
		return res;
	res = inf;
	
	if(r == n-1){
		res = 0;
	}else if(!isBlocked(r+1, c)){
		res= rec(r+1, c,c,c);
	} else{
		int left = c;	
		while((!isBlocked(r, left-1) || left-1 >= a)  && isBlocked(r+1, left-1))
			left--;
		int right = c;
		while((!isBlocked(r, right+1) || right+1 <= b) && isBlocked(r+1, right+1))
			right++;
		
		for(int aa = left + 1; aa <= right; aa++){
			for(int bb = aa; bb <= right; bb++){
				res = min(res, descTo(r+1, aa, aa, bb) + (bb - aa + 1));
			}
		}
		for(int aa = left; aa < right; aa++){
			for(int bb = aa; bb < right; bb++){
				res = min(res, descTo(r+1, bb,aa,bb) + (bb - aa + 1));
			}
		}

		if(!isBlocked(r, left-1) || left-1 >= a)
			res = min(res, descTo(r+1, left-1, left-1, left-1));
		if(!isBlocked(r, right+1) || right+1 <= b){
			res = min(res, descTo(r+1, right+1, right+1, right+1));
		}
	}

	return res;
}

int main(){
int np; cin>>np;
rep(tp,np){
	memset(DP,-1,sizeof(DP));
	cin >> n >> m >> f;
	grid = vector<string>(n);
	rep(i,n)
		cin >> grid[i];
	int hit = rec(0,0,0,0);
	printf("Case #%d: ", tp+1);
	if(hit == inf)
		printf("No\n");
	else
		printf("Yes %d\n", hit);
}
}	
