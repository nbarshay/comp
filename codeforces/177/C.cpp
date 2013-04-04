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

vector<int> match;

int highbit(int x){
	return x == 0 ? 0 : (1 + highbit(x>>1));
}

void rec(int at){
	if(at == -1)
		return;
	if(at == 0){
		match[0] = 0;
		return;
	}

	int cap = 1 << highbit(at);
	int ptrb = cap/2;
	int ptra = ptrb-1;
	while(ptrb <= at){
		match[ptrb] = ptra;
		match[ptra] = ptrb;
		ptra--;
		ptrb++;
	}

	rec(ptra);	
}

typedef long long ll;

int main(){
	int n; cin>>n;
	match = vector<int>(n+1);
	rec(n);
	
	ll acc = 0;
	rep(i, n+1)
		acc += i ^ match[i];
	cout << acc << endl;
	rep(i,n+1){
		if(i) cout << " ";
		cout << match[i];
	}
	cout << endl;
}	

