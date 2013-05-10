#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 3000000;
//!!!MAXE MUST BE DOUBLE NUMBER OF EDGES!!!
const int MAXE = 2 * 30000000;
const int INF = 1000000005;
const int CAPINF = 1000000005;

template <typename T> struct Dinic
{
    int V, source, sink;
    int eind, eadj [MAXE], eprev [MAXE], elast [MAXV], start [MAXV];
    int front, back, q [MAXV], dist [MAXV];
    T ecap [MAXE];

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
