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

typedef long long ll;

const ll mod = 1000000007;

ll add(ll a, ll b){
	return (a+b)%mod;
}

int n,m, col;

int main(){
	cin>>n>>m>>col;


	vector<vector<int> > v(n, vector<int>(m));
	rep(i,n) rep(k,m){
		char c;
		cin >> c;
		v[i][k] = c - '0';
	}
	if(n + m - 1 > 10){
		cout << 0 << endl;
		return 0;
	}
	if(m > 5){
		vector<vector<int> > v2(m, vector<int>(n));
		rep(i,n) rep(k,m)
			v2[k][i] = v[i][k];
		v = v2;
		swap(n,m);
	}

	assert(m <= 5);

	int powm[100];
	powm[0] = 1;
	For(i,1,100)
		powm[i] = powm[i-1]*(m+1);


	int sig = 0;
	rep(i, col)
		sig += powm[i]*m;

	cout << sig << " " << powm[col] << endl;

	cout << n << " " << m << " " << col << endl;
	cout << v << endl;

	map<int,int> mdp;
	mdp[sig] = 1;

	rep(i, n){
		map<int,int> next_m;
		cout << sz(mdp) << endl;
		foreach(it, mdp){
			int seed = it->F;
			int freq  = it->S;
			int pos[10];
			rep(k, col)
				pos[k] = (seed / powm[k]) % (m+1);

			rep(nseed, powm[col]){
				int pos2[10];
				rep(i, col)
					pos2[i] = (nseed / powm[i]) % (m+1);
				int cnt = 0;
				bool bad = false;

				int used[10];
				memset(used,0,sizeof(used));

				rep(i, col){
					if(pos2[i] > pos[i])
						bad = true;
					else if(pos2[i] < pos[i]){
						if(used[pos2[i]])
							bad = true;
						used[pos2[i]] = true;
						cnt++;
					}
				}
				rep(k, m) if(v[i][k] > 0){
					int col = v[i][k] - 1;
					if(pos2[col] != k || pos2[col] == pos[col])
						bad = true;
				}
				if(!bad && cnt == m)
					next_m[nseed] += freq;
			}
		}
		mdp = next_m;
	}
	ll res = 0;
	foreach(it, mdp)
		res += it->S;
	cout << res << endl;
}	
