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

#define MAXN 150

int B[MAXN][MAXN];

int main(){
int np; cin>>np;
rep(tp,np){
	int n,m; cin>>n>>m;
	rep(i,n) rep(k,m)
		cin >> B[i][k];
	bool ok = true;
	rep(i,n) rep(k,m){
		bool ok_col = true;
		rep(j,n) if(B[j][k] > B[i][k])
			ok_col = false;
		bool ok_row = true;
		rep(j,m) if(B[i][j] > B[i][k])
			ok_row = false;
		if(!(ok_col || ok_row))
			ok = false;
	}
	printf("Case #%d: %s\n", tp+1, ok ? "YES" : "NO");
}
}	

