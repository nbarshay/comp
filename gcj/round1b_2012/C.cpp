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

typedef long long ll;

#define MAXN 500

map<ll, vector<int> > m;
vector<ll> A;

void show(vector<int> v){
	rep(i, sz(v)){
		if(i) cout << " ";
		cout << A[v[i]];
	}
	cout << endl;
}

int main(){
int np; cin>>np;
rep(tp,np){
	int n; cin>>n;
	used.clear();
	m.clear();
	A = vector<ll>(n);
	rep(i,n)
		cin >> A[i];
	while(1){
		vector<int> hit;
		ll sum = 0;
		rep(i, 6){
			int idx = rand() % n;
			hit.pb(idx);
			sum += A[idx];
		}

		if(m.count(sum) && m[sum] != hit){
			printf("Case #%d:\n", tp+1);
			show(m[sum]);
			show(hit);
			break;
		} else{
			m[sum] = hit;
		}
	}
}
}	
