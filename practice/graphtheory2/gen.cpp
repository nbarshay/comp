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

const int n = 30000;

const int q = 30000;

int get(){
	return (rand()%n) + 1;
}

const int block = 100;

int main(){
	cout << n << " " << (n-1) << endl;
	For(i,2,n+1){
		cout << i << " " << i/2 << endl;
	}

	cout << q << endl;
	rep(i,q/2){
		cout << 0 << " " << get() << " " << get() << endl;

		cout << 1 << " " << get() << " " << get() << endl;
	}
}	

