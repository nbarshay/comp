/*
TASK: gravity
LANG: C++
*/


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

#define MAXN 505
int D[MAXN][MAXN][2];
char grid[MAXN][MAXN];
int n,m;
bool onBoard(int r, int c){
	return r>=0 && c>=0 && r < n && c < m;
}

deque<pair<pair<int,int>, int> > q;

void e_front(int r, int c, int d, int dist){
	if(D[r][c][d] != -1)
		return;
	D[r][c][d] = dist;
	q.push_front(mp(mp(r,c), d));
}

void e_back(int r, int c, int d, int dist){
	if(D[r][c][d] != -1)
		return;
	D[r][c][d] = dist;
	q.push_back(mp(mp(r,c), d));
}
int main(){
	freopen("gravity.in", "r", stdin);
	freopen("gravity.out", "w", stdout);

	cin>>n>>m;
	int sr,sc;
	rep(r,n){
		string s; cin>>s;
		rep(c,m){
			grid[r][c] = s[c];
			if(grid[r][c] == 'C'){
				sr = r, sc = c;
			}
		}
	}
	memset(D,-1,sizeof(D));
	e_back(sr,sc,0,0);
	int ans = -1;
	while(!q.empty()){
		int at_r = q.back().F.F, at_c = q.back().F.S, at_d = q.back().S;
		q.pop_back();
		int dist = D[at_r][at_c][at_d];
		if(grid[at_r][at_c] == 'D'){
			ans = D[at_r][at_c][at_d];
			break;
		}
		int down = at_d == 0 ? at_r + 1 : at_r - 1;
		if(!onBoard(down, at_c))
			continue;
		if(grid[down][at_c] == '#'){
			rep(k,2){
				int to_c = k ? at_c + 1 : at_c - 1;
				if(onBoard(at_r, to_c) && grid[at_r][to_c] != '#')
					e_back(at_r, to_c, at_d, dist);
			}
			e_front(at_r, at_c, 1 - at_d, dist+1);
		} else{
			e_back(down, at_c, at_d, dist);
		}
	}
	cout << ans << endl;	
	
}	

