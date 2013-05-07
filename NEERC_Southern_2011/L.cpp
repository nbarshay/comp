#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define IT(c) typeof((c).begin())
#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)
#define foreach(i, c) for(IT(c) i = (c).begin(); i != (c).end(); ++i)

#define sz(a) int((a).size())
#define mp make_pair
#define F first
#define S second
#define pb push_back

void output(vector<pair<int,int> >& swaps){
	cout << sz(swaps);
	foreach(it, swaps)
		cout << " " << (it->F + 1) << " " << (it->S + 1);
	cout << endl;
}


pair<vector<pair<int,int> >, vector<pair<int,int> > > solve(vector<int> cyc){
	int N = sz(cyc);

	vector<int> order(N);
	rep(i, N-1)
		order[i] = i+1;
	order[N-1] = 0;

	vector<pair<int,int> > r1;
	vector<pair<int,int> > r2;

	r1.pb(mp(cyc[0], cyc[1]));
	swap(order[0], order[1]);
	for(int a = 2, b = N-1; a < b; a++, b--){
		swap(order[a], order[b]);
		r1.pb(mp(cyc[a], cyc[b]));
	}

	vector<bool> V(N, false);
	rep(i,N) if(!V[i]){
		int at = i, to = order[at];
		V[at] = V[to] = true;
		if(at != to) {
			swap(order[at], order[to]);
			r2.pb(mp(cyc[at], cyc[to]));
		}
	}

	return(mp(r1, r2));
}


void doit(vector<int> dat){
	int N = sz(dat);

	vector<int> ord = dat;
	sort(ord.begin(), ord.end());

	multimap<pair<int,int>,int > dir;
	rep(i,N) if(ord[i] != dat[i]){
		dir.insert(mp(mp(ord[i],dat[i]), i));
	}
	bool fail = false;
	vector<pair<int,int> > swaps;
	while(1){
		IT(dir) it = dir.begin();
		if(it == dir.end())
			break;
		int a = it->F.F, b = it->F.S;
		int idx1 = it->S;
		IT(dir) it2 = dir.find(mp(b,a));
		if(it2 == dir.end()){
			fail = true;
			break;
		}
		int idx2 = it2->S;
		swaps.pb(mp(idx1, idx2));
		dir.erase(it);
		dir.erase(it2);
	}
	if(!fail){
		if(sz(swaps) == 0)
			cout << 0 << endl;
		else{
			cout << 1 << endl;
			output(swaps);
		}
	} else{
		vector<pair<int,int> > aug;
		rep(i,N)
			aug.pb(mp(dat[i], i));
		sort(aug.begin(), aug.end());
		vector<int> perm(N);
		rep(i,N)
			perm[aug[i].S] = i;
		vector<vector<int> > cyc;
		
		vector<int> vis(N, false);
		rep(i, N) if(!vis[i]){
			int at = i;
			vector<int> cur;
			do{
				vis[at] = true;
				cur.pb(at);
				at = perm[at];
			} while(at != i);
			if(sz(cur) > 1)
				cyc.pb(cur);
		}
			
		vector<pair<int,int> > r1, r2;
		foreach(it, cyc){
			pair<vector<pair<int,int> >, vector<pair<int,int> > > hit = solve(*it);
			foreach(it2, hit.F)
				r1.pb(*it2);
			foreach(it2, hit.S)
				r2.pb(*it2);
		}
		cout << 2 << endl;
		output(r1);
		output(r2);
	}
}

int main(){
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
	int N; cin>>N;
	vector<int> dat(N);
	rep(i,N)
		cin >> dat[i];

	doit(dat);	
		
}	
