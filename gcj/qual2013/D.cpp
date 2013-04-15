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

int nbox;

bool check(map<int,int> start, set<int> pop, vector<int> in, vector<vector<int> > out){

	map<int, set<int> > jump;
	set<int> need;

	rep(i, nbox){
		if(pop.count(i)){
			start[in[i]]--;
			foreach(it, out[i])
				start[*it]++;
		} else{
			foreach(it, out[i])
				jump[in[i]].insert(*it);
			need.insert(in[i]);
		}
	}

	set<int> seen;
	foreach(it, start){
		assert(it->S >= 0);
		if(it->S > 0)
			seen.insert(it->F);
	}

	set<int> nxt = seen;
	while(sz(nxt)){
		set<int> n_nxt;
		foreach(it, nxt){
			foreach(it2, jump[*it]){
				int col = *it2;
				if(!seen.count(col)){
					n_nxt.insert(col);
					seen.insert(col);
				}
			}
		}
		nxt = n_nxt;
	}
	foreach(it, need)
		if(seen.count(*it) == 0)
			return false;

	return true;
}

#define MAXK 200

int main(){
int np; cin>>np;
rep(tp,np){
	cerr << "Working... " << (tp+1) << endl;
	map<int,int> start;
	int nhave; cin>>nhave;
	cin>>nbox;

	vector<int> totalin(MAXK, 0);
	vector<int> totalout(MAXK, 0);

	rep(i, nhave){
		int t; cin>>t;
		t--;
		totalout[t]++;
		start[t]++;
	}


	vector<int> in(nbox);
	vector<vector<int> > out(nbox);

	rep(i, nbox){
		int a; cin>>a;
		a--;
		in[i] = a;
		totalin[a]++;
		int t; cin>>t;
		rep(j,t){
			int b; cin>>b;
			b--;
			totalout[b]++;
			out[i].pb(b);
		}
	}

	bool bad = false;
	rep(i, MAXK){
		if(totalin[i] > totalout[i]) 
			bad = true;
	}

	set<int> empty;
	if(!check(start, empty, in, out))
		bad = true;

	printf("Case #%d:", tp+1);

	if(bad){
		printf(" IMPOSSIBLE\n");
		continue;
	} 

	set<int> box_used;
	rep(iter, nbox){
		bool got = false;
		rep(i,nbox) if(!box_used.count(i)){

			map<int,int> cur = start;
			foreach(it, box_used){
				cur[in[*it]]--;
				foreach(it2, out[*it])
					cur[*it2]++;
			}
			if(cur[in[i]] <= 0)
				continue;

			set<int> test = box_used;
			test.insert(i);

			if(check(start, test, in, out)){
				box_used.insert(i);
				printf(" %d", i+1);
				got = true;
				break;
			}
		}
		assert(got);
	}
	printf("\n");

}
}	

