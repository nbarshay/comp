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

	
	srand(time(NULL));
	cout << rand() << endl;
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

	For(i,m,n)
		P[i] = rand() % nidx;

	int iter = 0;
	while(true){
		bool delta = false;
		For(i,m,n){
			double cost = getCost(i, P[i]);
			if(P[i] >= 0 && getCost(i, P[i]-1) < cost){
				P[i] = P[i]-1;
				delta = true;
			} else if(P[i] < nidx-1 && getCost(i, P[i]+1) < cost){
				P[i] = P[i]+1;
				delta = true;
			}
		}
		if(!delta)
			break;
		iter++;
	}
	double res = 0;
	rep(i, n)
		res += getCost(i, P[i]);
	cout << fixed << setprecision(10) << res/2.0 << endl;
	cout << iter << endl;
	/*
	rep(i,n)
		cout << L[P[i]] << " ";
	cout << endl;
	*/

}	

