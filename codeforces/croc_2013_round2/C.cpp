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

inline ll eval(const ll& a, const ll& b, const ll& c){
	ll x = a+b+c;	
	return x*x*x-a*a*a-b*b*b-c*c*c;
}

int main(){
	ll n; cin>>n;
	ll res = 0;
	For(a,1,n+1){
		if(eval(a,1,1) > n)
			break;
		ll b = 1;
		while(eval(a,b,1) < n && b <= a)
			b++;
		ll c = 1;
		for(;b >= 1; b--){
			while(eval(a,b,c) < n && c <= b)
				c++;
			if(c > b)
				break;
			if(eval(a,b,c) == n){
			//	cout << a << " " << b << " " << c << endl;
				if(a==b && b==c)
					res++;
				else if(a == b || b == c || c == a)
					res += 2;
				else
					res += 6;
			}
		}
	}
	cout << res << endl;
}	

