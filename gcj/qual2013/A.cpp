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

int dr[8] = {1,1,1,0,-1,-1,-1,0};
int dc[8] = {1,0,-1,-1,-1,0,1,1};
const int n=4;
char B[n][n];

char goal[2] = {'X', 'O'};

int main(){
int np; cin>>np;
rep(tp,np){
	rep(i,4){
		string s; cin>>s;
		rep(k,4)
			B[i][k] = s[k];
	}
	bool full = true;
	rep(i,n) rep(k,n) if(B[i][k] == '.')
		full = false;

	bool won[2];
	won[0] = won[1] = false;
	rep(k,2){
		rep(i, n) rep(j,n) rep(d, 8){
			int r = i, c = j;
			int cnt = 0;
			while(r >= 0 && c >= 0 && r < n && c < n){
				if(B[r][c] == goal[k] || B[r][c] == 'T')
					cnt++;
				r += dr[d]; c += dc[d];
			}
			if(cnt == 4)
				won[k] = true;
		}
	}
	assert(!(won[0] && won[1]));
	string res;
	if(won[0])
		res = "X won";
	else if(won[1])
		res = "O won";
	else if(full)
		res = "Draw";
	else
		res = "Game has not completed";
	printf("Case #%d: %s\n", tp+1, res.c_str());

}
}	

