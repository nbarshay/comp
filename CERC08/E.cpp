#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <deque>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <stack>
#include <assert.h>
#include <list>
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

typedef long long ll;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef vector<string> VS;
typedef pair<int, int> PI;

template<class T>
ostream& operator<<(ostream& out, vector<T> v){
	out << "[";
	rep(i, sz(v)){
		if(i) out << " ";
		out << v[i];
	}
	out << "]";
	return out;
}

vector<string> str;
int n;

vector<bool> is_inf;
vector<bool> does_vary;
vector<bool> inf_vary;

vector<int> mem;
bool isStatic(int at){
	int& res = mem[at];
	if(res >= 0)
		return res;

	if(!is_inf[at]){
		res = does_vary[at] ? 0 : 1;
	} else {
		bool got_var = false;
		for(char& c : str[at]){
			if(is_inf[c]){
				if(inf_vary[c])
					got_var = true;
				res = got_var ? 0 : 1;
				break;
			} else {
				if(!isStatic(c)) 
					got_var = true;
			}
		}
	}
	return res;
}

int main(){
int np; cin>>np;
rep(tp,np){
	cin >> n;
	str = vector<string>(n);
	rep(i,n){
		string s;
		cin>>s;
		for(char& c : s)
			c -= 'a';
		str[i] = s;
	}
	vector<vector<bool>> adj(n, vector<bool>(n, false));
	rep(i,n){
		for(char& c : str[i])
			adj[i][c] = true;
	}
	rep(j,n) rep(i,n) rep(k,n)
		if(adj[i][j] && adj[j][k])
			adj[i][k] = true;
	is_inf = vector<bool>(n, false);

	rep(i,n) rep(j,n) if(adj[i][j] && adj[j][i] && sz(str[j]) > 1)
		is_inf[i] = true;
	rep(i,n) rep(j,n) if(adj[i][j] && is_inf[j])
		is_inf[i] = true;

	vector<vector<bool> > inf(n, vector<bool>(n, false));
	rep(i, n) if(is_inf[i]){
		for(char& c : str[i]) if(is_inf[c]){
			inf[i][c] = true;
			break;
		}
	}

	inf_vary = vector<bool>(n, false);
	rep(i,n) rep(j,n) if(inf[i][j] && inf[j][i] && i != j)
		inf_vary[i] = true;
	rep(i,n) rep(j,n) if(inf[i][j] && inf_vary[j])
		inf_vary[i] = true;

	does_vary = vector<bool>(n, false);
	rep(i,n) rep(j,n) if(adj[i][j] && adj[j][i] && i != j)
		does_vary[i] = true;
	rep(i,n) rep(j,n) if(does_vary[j] && adj[i][j])
		does_vary[i] = true;

	//cout << is_inf << endl;
	//cout << does_vary << endl;

	mem = vector<int>(n, -1);
	cout << (isStatic(0) ? "YES" : "NO") << endl;	
}
}

