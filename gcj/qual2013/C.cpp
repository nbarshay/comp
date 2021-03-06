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

bool isPal(ll v){
	vector<ll> d;
	while(v){
		d.pb(v % 10);
		v /= 10;
	}
	for(ll i=0, j=sz(d)-1; i < j; i++,j--)
		if(d[i] != d[j])
			return false;
	return true;
}

bool check(ll v){
	if(isPal(v) && isPal(v*v))
		return true;
}

int main(){
	rep(i, 1000000000)
		if(check(i))
			cout << i << endl;
}	

