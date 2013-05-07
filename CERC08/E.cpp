#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

#define IT(c) typeof((c).begin())
#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)
#define foreach(i, c) for(IT(c) i = (c).begin(); i != (c).end(); ++i)

#define sz(a) int((a).size())
#define pb push_back


vector<vector<int> > A;
vector<bool> I;		//leads to infinite cycle
vector<int> finite_static;		//is finite vertex static
vector<int> infinite_static;	

bool finite_rec(int at){
	if(finite_static[at] >= 0)
		return finite_static[at];
	int& res = finite_static[at];
	res = 1;
	foreach(x, A[at])
		if(!finite_rec(*x))
			res = 0;
	return res;
}

bool rec(int at){
	if(infinite_static[at] >= 0)
		return infinite_static[at];

	foreach(x, A[at]){
		if(I[*x]){
			assert(*x != at);
			return rec(*x);
		} else{
			if(!finite_rec(*x))
				return false;
		}
	}
	assert(false);
}


int main(){
int cases; cin>>cases;
rep(cas, cases){
	int n; cin>>n;
	A = vector<vector<int> >(n);
	rep(i,n){
		string s; cin>>s;
		foreach(c,s)
			A[i].pb(*c - 'a');
	}

	vector<vector<int> > adj(n, vector<int>(n, 0));
	rep(at, n)
		foreach(to, A[at])
			adj[at][*to] = 1;
	rep(j,n) rep(i,n) rep(k,n)
		if(adj[i][j] && adj[j][k])
			adj[i][k] = 1;

	I = vector<bool>(n, false);		//leads to infinite cycle
	rep(i,n) rep(j,n) if(sz(A[j]) > 1 &&  adj[i][j] && adj[j][i])
		I[i] = true;

	rep(i,n) rep(j,n) if(I[j] && adj[i][j])
		I[i] = true;

	finite_static = vector<int>(n, -1);
	//compute static of finite vertices on cycles
	rep(i,n) if(!I[i] && adj[i][i])
		finite_static[i] = (A[i][0] == i ? 1 : 0);

	infinite_static = vector<int>(n, -1);
	rep(i,n) if(I[i]){
		vector<int> V(n, false);
		int at = i;
		bool got = false;
		int tot = 0;
		int len = 0;
		while(1){
			if(V[at])
				break;
			V[at] = true;
			len++;
			foreach(x, A[at]){
				if(I[*x]){
					at = *x;
					break;
				} else{
					tot++;
					if(!finite_rec(*x))
						got = true;
				}
			}
		}
		if(at == i)
			infinite_static[i] = (got || (tot == 0 && len > 1)) ? 0 : 1;
	}

	bool res;
	if(I[0])
		res = rec(0);
	else
		res = finite_rec(0);
	cout << (res ? "YES" : "NO") << endl;
}
}	
