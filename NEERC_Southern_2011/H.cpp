#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <assert.h>
using namespace std;

#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)
#define foreach(i, c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)

#define sz(a) int((a).size())
#define pb push_back
#define mp make_pair
#define F first
#define S second

vector<vector<int> > adj;
vector<vector<vector<int> > > segs;	

void dfs(int at, int from, vector<int>& vis){
	vis.pb(at);
	if(sz(adj[at]) == 4)
		return;
	foreach(it, adj[at]) if(*it != from)
		dfs(*it, at, vis);
}

const int NONE = 0, ONE = 1, TWO = 2;

int getAns(int a, int b, int len){
	if(a == NONE || b == NONE)
		return len;
	else if(a == b){
		if(len % 2)
			return len;
		else
			return len-1;
	} else if(a != b){
		if((len % 2) == 0)
			return len;
		else
			return len-1;
	}
}

void process(int s1, int s2, vector<int> path, pair<vector<int> , vector<int> >& ans){
	path.pop_back();
	int S = sz(path);

	if(s1 == NONE){
		swap(s1, s2);
		reverse(path.begin(), path.end());
	}

	vector<int> asn(S+2, 0);
	asn[0] = s1;
	asn[S+1] = s2;
	For(i,1,S+1){
		For(k,1,3){
			if(asn[i-1] != k && asn[i+1] != k)
				asn[i] = k;
		}
	}
	rep(i, S){
		int put = asn[i+1];
		if(put == 1)
			ans.F.pb(path[i]);
		else if(put == 2)
			ans.S.pb(path[i]);
	}
}

pair<vector<int>, vector<int> > pick(pair<vector<int>, vector<int> > a, 
		pair<vector<int>, vector<int> > b){
	if(sz(a.F) + sz(a.S) > sz(b.F) + sz(b.S))
		return a;
	else
		return b;
}

int main(){
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
	int N,M; cin>>N>>M;
	adj = vector<vector<int> >(N);
	rep(i,M){
		int a,b; cin>>a>>b;
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	int start = -1;
	rep(i,N) if(sz(adj[i]) == 4)
		start = i;

	int from = -1;
	int at = start;
	do{
		assert(sz(adj[at]) == 4);
		vector<vector<int> > paths;	
		foreach(it, adj[at]){
			vector<int> temp;
			dfs(*it, at, temp);
			paths.pb(temp);
		}
		int nxt = -1;
		foreach(it, paths) if(it->back() != from)
			nxt = it->back();

		vector<vector<int> > cur;
		foreach(it, paths) if(it->back() == nxt)
			cur.pb(*it);
		assert(sz(cur) == 2);
		segs.pb(cur);

		from = at;
		at = nxt;
	}while(at != start);

	pair<vector<int>, vector<int> > result;
	rep(start_state, 3){
		int S = sz(segs);
		vector<vector<int> > DP(S+1, vector<int>(3, -1));
		vector<vector<int> > back(S+1, vector<int>(3,-1));
		DP[S][start_state] = 0;
		for(int at = S-1; at >= 0; at--){
			rep(state, 3){
				rep(next_state, 3) if(DP[at+1][next_state] >= 0){
					int val = DP[at+1][next_state];
					rep(k,2){
						int len = sz(segs[at][k]) - 1;
						val += getAns(state, next_state, len);
					}
					if(state != NONE)
						val++;
					if(val > DP[at][state]){
						DP[at][state] = val;
						back[at][state] = next_state;
					}
				}
			}
		}

		pair<vector<int>, vector<int> > ans;		
		int state = start_state;
		rep(i, S){
			assert(state >= 0);
			int next_state = back[i][state];

			rep(k,2)
				process(state, next_state, segs[i][k], ans);
			int term = segs[i][0].back();
			if(next_state == ONE)
				ans.F.pb(term);
			else if(next_state == TWO)
				ans.S.pb(term);

			state = next_state;
		}

		result = pick(result, ans);
	}
	rep(k,2){
		vector<int>& cur = k ? result.S : result.F;
		cout << sz(cur);
		foreach(it, cur)
			cout << " " << (*it+1);
		cout << endl;
	}
}	
