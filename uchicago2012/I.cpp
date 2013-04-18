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

template<class T>
ostream& operator<<(ostream& out, vector<T> v){
	out << "[";
	rep(i, sz(v)){
		if(i) out << ", ";
		out << v[i];
	}
	out << "]";
	return out;
}
template<class A, class B>
ostream& operator<<(ostream& out, pair<A,B> p){
	out << "<" << p.F << ", " << p.S << ">";
	return out;
}
template<class T>
ostream& operator<<(ostream& out, set<T> s){
	out << "(";
	foreach(it, s){
		if(it != s.begin()) out << ", ";
		out << *it;
	}
	out << ")";
	return out;
}
template<class A, class B>
ostream& operator<<(ostream& out, map<A,B> m){
	out << "{";
	foreach(it, m){
		if(it != m.begin()) out << ", ";
		out << *it;
	}
	out << "}";

}

const int MAXV = 80*5;
const int MAXE = MAXV*100;
const int INF = 1000000005;
const int CAPINF = 1000000005;

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
	
	vector<pair<int,int> >  getEdges(){
		vector<pair<int,int> > res;
		rep(i,V){
			for(int e = elast[i]; e!=-1; e = eprev[e]){
				int v = eorig[e] - ecap[e];
				if(v > 0 && emark[e]){
					res.pb(mp(i, eadj[e]));
				}
			}
		}
		return res;
	}

    inline void addEdge (int a, int b, T cap1, T cap2, bool mark=false)
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

int n;

const int SOURCE = 0;
const int SINK = 1;

const int IN = 0;
const int OUT = 1;

int getIndex(int idx, int type){
	return 2 + idx*2 + type;
}

vector<string> adj;

bool doProblem(int num){
	dinic.init(getIndex(n,OUT));
	rep(i,n){
		dinic.addEdge(SOURCE, getIndex(i, IN), num, 0);
		dinic.addEdge(getIndex(i, OUT), SINK, num, 0);
	}
	rep(i,n) rep(k,n) if(adj[i][k] == 'Y')
		dinic.addEdge(getIndex(i, IN), getIndex(k, OUT), 1, 0, true);

	int hit = dinic.flow(SOURCE, SINK);
	return hit == n*num;
}

int main(){
while(1){
	cin>>n;
	if(n==0)
		break;
	adj = vector<string>(n);
	rep(i,n)
		cin >> adj[i];
	int a = 0, b = n;
	while(a != b){
		int m = (a+b+1)/2;
		if(doProblem(m)){
			a = m;
		} else{
			b = m-1;
		}
	}
	doProblem(a);
	set<pair<int,int> > used;
	vector<pair<int,int> > edges = dinic.getEdges();

	vector<vector<int> > res(a, vector<int>(n, -1));
	rep(iter, a){
		dinic.init(getIndex(n, OUT));
		
		foreach(it, edges) if(!used.count(*it))
			dinic.addEdge(it->F, it->S, 1, 0, true);
		rep(i,n){
			dinic.addEdge(SOURCE, getIndex(i, IN), 1,0);
			dinic.addEdge(getIndex(i, OUT), SINK, 1,0);
		}

		int hit = dinic.flow(SOURCE,SINK);
		assert(hit == n);

		vector<pair<int,int> > cur = dinic.getEdges();
		foreach(it, cur){
			used.insert(*it);
			int a = (it->F - 2)/2;
			int b = (it->S - 2)/2;
			res[iter][b] = a;
		}
	}

	cout << a << endl;
	rep(i,a){
		rep(k,n){
			if(k) cout << " ";
			assert(res[i][k] >= 0);
			cout << res[i][k]+1;
		}
		cout << endl;
	}

}
}	
