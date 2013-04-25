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

#define MAXN 55

int n,m,f;
vector<string> grid;

bool isBlocked(int r, int c){
	if(r < 0 || c < 0 || r >= n || c >= m)
		return true;
	else
		return grid[r][c] == '#';
}
int fallFrom(int r, int c){
	int fell = 0;
	while(!isBlocked(r+1, c)){
		fell++;
		r++;
	}
	if(fell > f)
		return -1;
	return r;
}
deque<pair<int,int> > q;
vector<vector<int> > D;

int inf = 1000000000;

int main(){
int np; cin>>np;
rep(tp,np){
	cin>>n>>m>>f;
	grid = vector<string>(n);
	rep(i,n)
		cin >> grid[i];
	D = vector<vector<int> >(n, vector<int>(m,inf));
	vector<vector<bool> > V(n, vector<bool>(m, false));
	q = deque<pair<int,int> >();
	D[0][0] = 0;
	q.push_back(mp(0,0));
	int res = -1;
	while(!q.empty()){
		int r = q.front().F, c = q.front().S; q.pop_front();
		printf("%d %d\n", r,c);
		if(V[r][c])
			continue;
		V[r][c] = true;
		int dist = D[r][c];
		if(r == n-1){
			res = dist;
			break;
		}
		rep(k,2){
			int c2 = k ? c-1 : c+1;
			if(!isBlocked(r, c2)){
				int r2 = fallFrom(r, c2);
				if(r2 == -1) continue;
				D[r2][c2] = min(D[r2][c2], dist);
				q.push_front(mp(r2, c2));
			}
		}
		rep(k,2){
			int c2 = k ? c-1 : c+1;
			if(!isBlocked(r, c2) && isBlocked(r+1, c2)){
				int r2 = fallFrom(r+1, c2);	
				if(r2 == -1) continue;
				D[r2][c2] = min(D[r2][c2], dist+1);
				q.push_back(mp(r2, c2));
			}
		}
	}
	printf("Case #%d: ", tp+1);
	if(res == -1)
		printf("No\n");
	else
		printf("Yes %d\n", res);
}
}
