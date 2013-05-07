#include <iostream>
#include <string>
#include <fstream>
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

#define MAXN 600

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

int n,m;
int D[MAXN][MAXN];
int D2[MAXN][MAXN];

struct Node{
	int a,b;
	int sum;
	Node* left;
	Node* right;

	Node(int _a, int _b, int x) : a(_a), b(_b){
		if(a == b){
			sum = D[a][x];
			left = right = NULL;
		} else{
			int m = (a+b)/2;
			left = new Node(a,m, x);
			right = new Node(m+1, b, x);
			sum = left->sum + right->sum;
		}
	}
	int get(int low, int high){
		if(high < a || low > b){
			return 0;
		} else if(low <= a && high >= b){
			return sum;
		} else{
			return left->get(low, high) + right->get(low, high);
		}
	}
};

int getWeight(int size, int col){
	if(size % 2){
		int hit = abs(col - size/2) * 2;
		return col < size/2 ? -hit : hit;
	} else{
		if(col < size/2)
			return -((size/2-col)*2 - 1);
		else
			return (col - size/2)*2 + 1;
	}
}

vector<pair<int,pair<int,int> > > doit(){
	Node* root[m];
	rep(c, m){
		root[c] = new Node(0, n-1, c);
	}
	vector<pair<int, pair<int,int> > > res;
	For(size, 3, min(n,m) + 1){
		for(int base_r = 0; base_r + size <= n; base_r++){
			int sum = 0;
			int center = 0;
			rep(c, size){
				int r1 = (c==0 || c == size-1) ? base_r + 1 : base_r;
				int r2 = (c==0 || c == size-1) ? base_r + size - 2 : base_r + size - 1;
				int hit = root[c]->get(r1, r2);
				sum += hit;
				center += hit*getWeight(size, c);
			}
			for(int base_c = 0; true; base_c++){
				if(center == 0){
					res.pb(mp(size, mp(base_r * 2 + (size-1), base_c*2 + (size-1))));
				}
				if(base_c + size == m)
					break;

				int hit = root[base_c]->get(base_r + 1, base_r + size - 2);
				sum -= hit;
				center -= hit*getWeight(size, 0);

				rep(k,2){
					hit = D[k ? base_r : base_r + size - 1][base_c + 1];
					sum -= hit;
					center -= hit*getWeight(size, 1);
				}

				center -= 2*sum;	//shift body

				rep(k,2){
					hit = D[k ? base_r : base_r + size - 1][base_c + size - 1];
					sum += hit;
					center += hit*getWeight(size, size-2);
				}

				hit = root[base_c + size]->get(base_r + 1, base_r + size - 2);
				sum += hit;
				center += hit*getWeight(size, size-1);
			}
		}
	}
	return res;
}


int main(){
ifstream fin("B.in");

int np; cin>>np;
rep(tp,np){
	cerr << "Proc: " << tp << endl;
	cin >> n >> m;
	int garbage; cin>>garbage;
	rep(r,n){
		string s; cin>>s;
		rep(c,m){
			D[r][c] = s[c] - '0';
		}
	}
	vector<pair<int, pair<int,int> > > r1 = doit();	
	pair<int,int> test(5,6);
	set<pair<int, pair<int,int> > > lookup;
	foreach(it, r1)
		lookup.insert(*it);

	memcpy(D2,D, sizeof(D));	
	rep(r,n) rep(c,m){
		D[c][r] = D2[r][c];
	}
	swap(n,m);
	vector<pair<int, pair<int,int> > > r2 = doit();
	int res = -1;
	foreach(it, r2){
		if(lookup.count(mp(it->F, mp(it->S.S, it->S.F)))){
			res = max(res, it->F);
		}
	}
	printf("Case #%d: ", tp+1);
	if(res == -1)
		cout << "IMPOSSIBLE" << endl;
	else
		cout << res << endl;
}
}	

