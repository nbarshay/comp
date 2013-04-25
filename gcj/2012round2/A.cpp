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


typedef long long ll;

int main(){
int np; cin>>np;
rep(tp,np){
	ll n; cin>>n;
	ll X[n], L[n];
	rep(i,n)
		cin >> X[i] >> L[i];
	ll goal; cin>>goal;

	bool suc = false;
	queue<pair<ll,ll> > q;	//<how far forwards, pos>
	q.push(mp(2*X[0], X[0]));
	if(2*X[0] >= goal)
		suc = true;
	For(i,1,n){
		while(!q.empty() && q.front().F < X[i])
			q.pop();
		if(q.empty())
			break;
		ll len = min(X[i] - q.front().S, L[i]);
		ll to_pos = X[i] + len;
		if(to_pos >= goal)
			suc = true;
		if(to_pos > q.back().F)
			q.push(mp(to_pos, X[i]));
	}
	printf("Case #%d: %s\n", tp+1, suc ? "YES" : "NO");
}
}

