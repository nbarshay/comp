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

const int MAXV = 400;
const int MAXE = MAXV*MAXV + 2*MAXV;
const int INF = 1000000005, CAPINF = 1000000005;

template <typename T> struct Dinic
{
    int V, source, sink;
    int eind, eadj [MAXE], eprev [MAXE], elast [MAXV], start [MAXV];
    int front, back, q [MAXV], dist [MAXV];
    T ecap [MAXE];

	vector<pair<int,int> > cut(int source, int sink){
		const int tinf = 0x4f4f4f4f;
		vector<pair<int,int> > res;

		flow(source, sink);
		bfs();
		rep(at, V){
			for(int i = elast[at]; i != -1; i = eprev[i]) if((i&1) == 0){
				int to = eadj[i];		
				if(dist[at] != tinf && dist[to] == tinf)
					res.pb(mp(at,to));
			}
		}
		
		return res;	
	}

    inline void init (int v)
    {
        V = v; eind = 0;
        memset (elast, -1, V * sizeof (int));
    }

    inline void addedge (int a, int b, T cap1, T cap2)
    {
        eadj [eind] = b; ecap [eind] = cap1; eprev [eind] = elast [a]; elast [a] = eind++;
        eadj [eind] = a; ecap [eind] = cap2; eprev [eind] = elast [b]; elast [b] = eind++;
    }

    bool bfs ()
    {
        memset (dist, 0x4f, V * sizeof (int));
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


#define MAXN 300 
double C[MAXN][MAXN];
int P[MAXN];
double L[MAXN];
int n,m;

double getCost(int cow, int loc){
	double res = 0.0;
	rep(i,n) if(i != cow){
		res += abs(L[P[i]] - L[loc])*(C[i][cow] + C[cow][i]);
	}
	return res;
}

int main(){
	cin>>n>>m;
	set<double> vals;
	vector<double> raw(m);
	rep(i,m){
		double x;
		cin >> x;
		raw[i] = x;
		vals.insert(x);
	}
	rep(i,n) rep(k,n)
		cin >> C[i][k];

	int nidx = 0;
	foreach(it, vals){
		L[nidx++] = *it;
	}

	memset(P,0,sizeof(P));
	rep(i,m){
		int got = 0;
		rep(k, nidx)
			if(L[k] == raw[i]){
				P[i] = k;
				got++;
			}
		assert(got == 1);
	}

	vector<int> cur;
	For(i,m,n)
		cur.pb(i);

	rep(at, nidx-1){
		int ncur = sz(cur);
		Dinic<double> dinic;
		dinic.init(ncur + 2);
		int SOURCE = ncur;
		int SINK = ncur+1;
		rep(j, sz(cur)){
			rep(k,2){
				int kat = k == 0 ? at : at + 1;
				double cst = 0.0;
				rep(i,n) if(P[i] != at || i < m)
					cst += abs(L[P[i]] - L[kat])*(C[i][cur[j]] + C[cur[j]][i]);
				if(k == 0)
					dinic.addedge(SOURCE, j, cst, 0.0);
				else
					dinic.addedge(j, SINK, cst, 0.0);
			}
		}
		rep(i, sz(cur)) For(j,i+1, sz(cur)){
			double cost = (L[at+1] - L[at])*(C[cur[i]][cur[j]] + C[cur[j]][cur[i]]);
			dinic.addedge(i,j,cost, cost);
		}
		vector<pair<int,int> > hit = dinic.cut(SOURCE, SINK);
		bool move[ncur], stay[ncur];
		memset(move,0,sizeof(move));
		memset(stay,0,sizeof(stay));
		foreach(it, hit){
			pair<int,int> bla = *it;
			if(bla.F == SOURCE)
				stay[bla.S] = true;
			if(bla.S == SINK)
				move[bla.F] = true;
		}
		vector<int> n_cur;
		rep(i,ncur){
			assert(move[i] != stay[i]);
			if(move[i]){
				P[cur[i]] = at+1;
				n_cur.pb(cur[i]);
			}
		}
		cur = n_cur;
	}

	
	double res = 0;
	rep(i, n)
		res += getCost(i, P[i]);
	cout << fixed << setprecision(5) << res/2.0 << endl;
	/*
	rep(i,n)
		cout << L[P[i]] << " ";
	cout << endl;
	*/

}	

