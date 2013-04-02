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

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int MAXV = 2*MAXN + 2;
const int MAXE = MAXV*MAXV + 2*MAXV;
const int INF = 1000000005, CAPINF = 1000000005;

int n;

const int SOURCE = 0;
const int SINK = 1;
const int HELL = 2;
const int EXIT = 3;

int idx(int v){
	return 4 + v;
}

template <typename T> struct Dinic
{
    int V, source, sink;
    int eind, eadj [MAXE], eprev [MAXE], elast [MAXV], start [MAXV], emark[MAXE], eorig[MAXE];
    int front, back, q [MAXV], dist [MAXV];
    T ecap [MAXE];

    inline void init (int v)
    {
        V = v; eind = 0;
        memset (elast, -1, V * sizeof (int));
    }
	
	vector<map<int,int> > getEdges(){
		int num = idx(n-1)+1;

		vector<map<int,int> > res(num);
		rep(i,num){
			for(int e = elast[i]; e!=-1; e = eprev[e]){
				int v = eorig[e] - ecap[e];
				if(v > 0 && emark[e]){
					res[i][eadj[e]] += v;
				}
			}
		}
		return res;
	}

    inline void addedge (int a, int b, T cap1, T cap2, bool mark=false)
    {
        eadj [eind] = b; ecap [eind] = cap1; eprev [eind] = elast [a]; 
		emark[eind] = mark;	eorig[eind] = cap1;
		elast [a] = eind++;
		
        eadj [eind] = a; ecap [eind] = cap2; eprev [eind] = elast [b]; 
		emark[eind] = false; eorig[eind] = cap2;
		elast [b] = eind++;
    }

    bool bfs ()
    {
        memset (dist, 63, V * sizeof (int));
        front = back = 0;
        q [back++] = source; dist [source] = 0;

        while (front < back)
        {
            int top = q [front++];

            for (int i = elast [top]; i != -1; i = eprev [i])
                if (ecap [i] > 0 && dist [top] + 1 < dist [eadj [i]])
                {
                    dist [eadj [i]] = dist [top] + 1;
                    q [back++] = eadj [i];
                }
        }

        return dist [sink] < INF;
    }

    T dfs (int num, T pcap)
    {
        if (num == sink)
            return pcap;

        T total = 0;

        for (int &i = start [num]; i != -1; i = eprev [i])
            if (ecap [i] > 0 && dist [num] + 1 == dist [eadj [i]])
            {
                T p = dfs (eadj [i], min (pcap, ecap [i]));
                ecap [i] -= p;
                ecap [i ^ 1] += p;
                pcap -= p;
                total += p;

                if (pcap == 0)
                    break;
            }

        return total;
    }

    T flow (int _source, int _sink)
    {
        if (V == 0)
            return -1;

        source = _source; sink = _sink;
        T total = 0;
        while (bfs ())
        {
            memcpy (start, elast, V * sizeof (int));
            total += dfs (source, CAPINF);
        }

        return total;
    }
};

Dinic<int> dinic;



const int BIG = 1000;

vector<vector<int> > adj(n);

int doit(int m){
	dinic.init(idx(n-1) + 1);
	rep(from, n){
		foreach(it, adj[from]){
			int to = *it;
			dinic.addedge(idx(from), idx(to), BIG, 0, true);

			dinic.addedge(SOURCE, idx(to), 1, 0);
			dinic.addedge(idx(from), SINK, 1, 0);
		}
	}

	rep(i,n)
		dinic.addedge(HELL, idx(i), BIG, 0, true);
	rep(i, n)
		dinic.addedge(idx(i), EXIT, BIG, 0, true);

	dinic.addedge(EXIT, SINK, m, 0);
	dinic.addedge(SOURCE, HELL, m, 0);
	
	return dinic.flow(SOURCE, SINK);
}

void dfs(int at, vector<map<int,int> >& adj, vector<int>& path){
	path.pb(at);
	foreach(it, adj[at]) if(it->S > 0){
		it->S--;
		dfs(it->F, adj, path);
		return;
	}
	//assert(at == EXIT);
}


int main(){
	cin>>n;

	adj = vector<vector<int> >(n);
	int nedge = 0;
	rep(i,n){
		int t; cin>>t;
		nedge += t;
		rep(k,t){
			int v; cin>>v;
			v--;
			adj[i].pb(v);
		}
	}

	int a = 0, b = nedge;
	while(a != b){
		int m = (a+b)/2;

		int res = doit(m);
		if(res == nedge + m){
			b = m;
		} else{
			a = m+1;
		}
	}

	doit(a);
	vector<map<int,int> > edge = dinic.getEdges();

	rep(from, n)
		foreach(to, adj[from])
			edge[idx(from)][idx(*to)]++;

	cout << a << endl;
	rep(i,a){
		vector<int> path;
		dfs(HELL, edge, path);
		For(i,1, sz(path)-1){
			if(i > 1) cout<<" ";
			cout << path[i] - 3;
		}
		cout<<endl;
	}

	/*
	cout << a << endl;
	rep(i, sz(edge))
		for(auto x : edge[i])
			cout << i << "-" << x.S << "-->" << x.F << endl;
	*/

}	

