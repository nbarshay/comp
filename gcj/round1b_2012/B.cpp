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

int tr[4] = {1,-1,0,0};
int tc[4] = {0,0,1,-1};

int main(){
int np; cin>>np;
rep(tp,np){
	int height, n,m; cin>>height >> n >> m;

	vector<vector<int>> low(n, vector<int>(m)), high(n, vector<int>(m));
	rep(i,n) rep(k,m) cin >> high[i][k];
	rep(i,n) rep(k,m) cin >> low[i][k];

	vector<vector<int>> D(n, vector<int>(m,inf));
	D[0][0] = -(n*m)*100 - 1000;
	typedef pair<int, pair<int,int>> State;
	priority_queue<State, vector<State>, greater<State>> pq;
	pq.push(mp(D[0][0], mp(0,0)));
	while(!pq.empty()){
		int d = pq.top().F, r = pq.top().S.F, c = pq.top().S.S;
		pq.pop();
		if(d > D[r][c])
			continue;
		rep(dir, 4){
			int dr = r+tr[dir], dc = c+tc[dir];
			if(dr < 0 || dc < 0 || dr >= n || dc >= m)
				continue;
			if(low[r][c] > high[dr][dc]-50)
				continue;
			if(low[dr][dc] > high[r][c] - 50)
				continue;
			if(low[dr][dc] > high[dr][dc] - 50)
				continue;

			int inter = height + 50 - high[dr][dc];
			if(inter <= 0)
				inter = d;

			int first_time = max(d, inter);
			bool fast = height - first_time >= low[r][c] + 20;
			int hit = first_time + (fast ? 10 : 100);
			if(hit < D[dr][dc]){
				D[dr][dc] = hit;
				pq.push(mp(hit, mp(dr, dc)));
			}
		}
	}
	printf("Case #%d: %.1f\n", tp+1, max(double(D[n-1][m-1])/10.0, 0.0));
}
}	

