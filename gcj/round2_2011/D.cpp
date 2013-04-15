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

typedef vector<int> Vi;
typedef vector<vector<int> > Vvi;
typedef vector<string> Vs;
typedef pair<int, int> Pi;

template<class A, class B>
ostream& operator<<(ostream& out, const pair<A,B>& p){
	out << "<" << p.F << ", " << p.S << ">";
}

template<class T>
ostream& operator<<(ostream& out, const vector<T>& v){
	out << "[";
	rep(i, sz(v)){
		if(i) out << ", ";
		out << v[i];
	}
	out << "]";
}

template<class T>
ostream& operator<<(ostream& out, const set<T>& v){
	out << "(";
	bool first = true;
	foreach(it, v){
		if(first)
			first = false;
		else
			out << ", ";
		out << *it;
	}
	out << ")";
}

const int MAXN = 500;
vector<set<int> > adj;
vector<set<int> > dag;

int n,m;
int pre1;
int pre2;

const int source = 0;
const int sink = 1;

int mem[MAXN][MAXN];
int dp(int at, int last){
	if(mem[at][last] >= 0)
		return mem[at][last];
	if(at == pre2)
		return 1;

	int& res = mem[at][last];
	res = 0;
	foreach(it, dag[last]){
		int next = *it;
		int hit = 0;
		foreach(it2, adj[at]){
			if(adj[last].count(*it2))
				continue;
			if(adj[next].count(*it2))
				continue;
			if(*it2 == last)
				continue;
			hit++;
		}
		hit += dp(last, next) - 1;
		res = max(res, hit);
	}
	return res;	
}

int main(){
int np; scanf("%d", &np);
rep(tp,np){
	memset(mem,-1,sizeof(mem));
	scanf("%d %d", &n, &m);
	n += 2;
	pre1 = n-2;
	pre2 = n-1;
	adj = vector<set<int> >(n);
	dag = vector<set<int> >(n);

	rep(i,m){
		int a,b;
		scanf("%d,%d",&a, &b);
		adj[a].insert(b);
		adj[b].insert(a);
	}
	adj[pre1].insert(pre2);
	adj[pre2].insert(pre1);
	adj[pre2].insert(source);
	adj[source].insert(pre2);
	queue<int> q;	
	vector<int> D(n, -1);
	D[pre1] = 0;
	q.push(pre1);
	while(!q.empty()){
		int top=q.front();
		q.pop();
		foreach(it, adj[top]) if(D[*it] == -1){
			D[*it] = D[top]+1;
			q.push(*it);
		}
	}
	rep(i, n) foreach(it, adj[i]) if(D[i] == D[*it] + 1)
		dag[i].insert(*it);

	int res = 0;
	foreach(it, dag[sink]) foreach(it2, dag[*it])
		res = max(res, dp(*it, *it2));
	printf("Case #%d: %d %d\n", tp+1, D[sink] - 3, res);
}
}	

