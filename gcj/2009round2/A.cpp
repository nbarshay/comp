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


int main(){
int np; cin>>np;
rep(tp,np){
	int n; cin>>n;
	vector<string> v(n);
	vector<int> len(n);
	rep(i,n){
		cin >> v[i];
		len[i] = -1;
		rep(k,n) if(v[i][k] == '1')
			len[i] = k;
	}
	vector<bool> used(n);
	int res = 0;
	rep(i,n){
		int cnt = 0;
		rep(k,n) if(!used[k]){
			if(len[k] <= i){
				used[k] = true;
				break;
			} else{
				cnt++;
			}
		}
		res += cnt;
	}
	printf("Case #%d: %d\n", tp+1, res);

}
}

