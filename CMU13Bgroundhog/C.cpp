#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <deque>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <stack>
#include <assert.h>
#include <list>
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

#define TWO(x) (1<<(x))

typedef long long ll;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef vector<string> VS;
typedef pair<int, int> PI;

double getAngle(double op, double adj1, double adj2){
	return acos((adj1*adj1 + adj2*adj2 - op*op)/(2*adj1*adj2));
}

double getDist(double rad, double base, double adj, double op){
	double alpha = getAngle(op, base, adj)/2.0;
	return rad / tan(alpha);
}

int main(){
	int tp = 0;
	while(1){
		double L[3];
		double R1[3];
		double R2[3];
		rep(i,3)
			cin >> L[i];
		rep(i,3){
			cin>> R1[i] >> R2[i];
			R1[i]/=2.0;
			R2[i]/=2.0;
		}
		if(L[0] == 0 && L[1] == 0 && L[2] == 0)
			break;
		
		double S = (0.5)*(L[0] + L[1] + L[2]);
		double K = sqrt(S*(S - L[0])*(S - L[1])*(S-L[2]));
		double inrad = (2*K)/(2*S);

		vector<int> P;
		rep(i,3)
			P.pb(i);

		bool ok = false;
		do{
			rep(seed, TWO(3)){
				int acc = 0;
				rep(k,3){
					int a = P[k];
					int b = P[(k+1)%3];
					int c = P[(k+2)%3];

					double left = L[c];
					double right = L[b];
					double base = L[a];
					double d1 = getDist(R2[k], base, left, right);
					double d2 = getDist(R2[(k+1)%3], base, right, left);
					
					double gap = base - d1 - d2;
					if(gap < 0)
						break;

					double rdiff = R2[k] - R2[(k+1)%3];
					double d = sqrt(gap*gap + rdiff*rdiff);

					#define SWITCH(k) ((TWO(k) & seed) ? R1[k] : R2[k])
					#define SWITCH2(k) (!(TWO(k) & seed) ? R1[k] : R2[k])

					double sum1 = SWITCH(k) + SWITCH((k+1)%3);
					double sum2 = SWITCH2(k) + SWITCH2((k+1)%3);
					if(sum1 <= d && sum2 <= d)
						acc++;
				}
				if(acc == 3)
					ok = true;
			}

		}while(next_permutation(P.begin(), P.end()));

		rep(i,3)
			if(R2[i] > inrad)
				ok = false;

		if(tp)
			cout << endl;
		cout << "Triangle number " << (++tp) << ":"<<endl;

		if(ok)
			cout <<"All three stoppers will fit in the triangular space" << endl;
		else
			cout <<"Stoppers will not fit in the triangular space" << endl;
	}

}

