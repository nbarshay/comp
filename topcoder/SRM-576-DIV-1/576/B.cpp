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

const int inf = 1000000000;

const int MAXN =1000005;

#define SQ(x) ((x)*(x))

int n,c;

int P[MAXN];

int DP[MAXN];

template<class T>
ostream& operator<<(ostream& out, vector<T> v){
	out << "[";
	rep(i, sz(v)){
		if(i) out << " ";
		out << v[i];
	}
	out << "]";
	return out;
}

int rec(int at){
	if(at == 0)
		return 0;
	int& res = DP[at];
	if(res >= 0)
		return res;
	int a = 0, b = (at-1);

	vector<int> v;
	rep(i, at){
		v.pb(rec(i) + SQ(P[at-1] - P[i]) + c);
	}
	cout << v << endl;
	/*while(a != b){
		int m1 = max(((a+b))/3, a);
		int m2 = min((a+b)*2/3, b);
		
		int q1 = rec(m1) + SQ(P[at-1] - P[m1]) + c;
		int q2 = rec(m2) + SQ(P[at-1] - P[m2]) + c;
		if(q1 < q2)
			b = m2-1;
		else
			a = m1+1;
	}
	return (res = rec(a) + SQ(P[at-1] - P[a]) + c);
	*/
	res = inf;
	rep(i, at)
		res = min(res, rec(i) + SQ(P[at-1] - P[i]) + c);
	return res;
}

int main(){
while(1){
	cin >> n >> c;
	if(n==0)
		break;
	rep(i,n)
		cin >> P[i];
	sort(&P[0], &P[n]);
	memset(DP, -1, (n+1)*sizeof(int));
	cout << rec(n) << endl;
}
}	

