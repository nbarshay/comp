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

ll tab[9] = {1, 1, 2, 9, 64, 625, 7776, 117649, 2097152};

ll doit(int n){
	int pown[n+1];
	pown[0] = 1;
	For(i,1,n+1)
		pown[i] = pown[i-1]*n;
	int res = 0;
	rep(seed, pown[n]){
		int p[n];
		rep(i,n)
			p[i] = (seed / pown[i]) % n;
		bool good = true;
		For(i,1,n){
			int at = i;
			rep(j,n) if(at != 0)
				at = p[at];
			if(at != 0)
				good = false;
		}
		if(good)
			res++;
	}
	return res;
}

const ll MOD = 1000000007;
ll add(const ll& a, const ll& b) { return (a+b)%MOD;}
ll mul(const ll& a, const ll& b) {return (a*b)%MOD;}


int main(){
	/*
	cout <<"{";
	rep(i, 9){
		if(i) cout<<", ";
		cout << doit(i);
	}
	cout <<"}"<<endl;
	return 5;
	*/

	int n,k; cin>>n>>k;
	ll base = tab[k];
	
	For(i, k+1, n+1)
		base = mul(base, n - k);

	cout << base << endl;
}	

