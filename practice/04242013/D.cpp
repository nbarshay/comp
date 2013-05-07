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

int dr[8] = {-1,1,2,2,1,-1,-2,-2};
int dc[8] = {2,2,1,-1,-2,-2,-1,1};

const int MAXN = 100;

int main(){
	int n,m, sr, sc, gr, gc; 
	while(cin>>n>>m>>sr>>sc>>gr>>gc){
		int D[MAXN][MAXN];
		memset(D,-1,sizeof(D));
		sr--; sc--; gr--; gc--;
		D[sr][sc] = 0;
		queue<pair<int,int> > q;
		q.push(mp(sr,sc));
		while(!q.empty()){
			int r = q.front().F, c = q.front().S;
			q.pop();
			rep(d,8){
				int tr = r+dr[d], tc = c+dc[d];
				if(tr < 0 || tc < 0 || tr >= n || tc >= m || D[tr][tc] >= 0)
					continue;
				D[tr][tc]= D[r][c] + 1;
				q.push(mp(tr,tc));
			}
		}
		if(D[gr][gc] < 0)
			printf("impossible\n");
		else
			printf("%d\n", D[gr][gc]);
	}
}	
