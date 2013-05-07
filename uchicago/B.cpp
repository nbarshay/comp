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

typedef int(*COMP)(int,int);

struct Node{
	int a,b;
	Node* left;
	Node* right;

	int val;

	COMP comp;
	
	Node(vector<pair<int,int> >& v, int low, int high, COMP _comp) : comp(_comp) {
		a = v[low].F;
		b = v[high-1].F;

		if(low + 1 == high){
			left = right = NULL;
		} else{
			int piv = (low + high)/2;
			left = new Node(v, low, piv, comp);
			right = new Node(v, piv, high, comp);
		}

		val = comp(a,b);
	}

	void put(int loc, int t){
		if(loc > b || loc < a)
			return;

		val = comp(val, t);
		if(a != b){
			left->put(loc, t);
			right->put(loc, t);
		}
	}

	void get(int low, int high, int* v){
		if(low > b || high < a)
			return;

		if(low <= a && high >= b){
			*v = comp(*v, val);
		} else{
			left->get(low, high, v);
			right->get(low, high, v);
		}
	}
};

int min_fun(int a, int b){ return min(a,b);}
int max_fun(int a, int b){ return max(a,b);}

const int inf = 1000000005;

int main(){
	while(1){
		int n; cin>>n;
		if(n==0) 
			break;
		map<int,int> loc_to_idx;
		vector<pair<int,int> > dat(n);
		rep(i,n){
			cin >> dat[i].F >> dat[i].S;
			loc_to_idx[dat[i].F] = i;
		}

		sort(dat.begin(), dat.end());

		Node* min_root = new Node(dat, 0, n, min_fun);
		Node* max_root = new Node(dat, 0, n, max_fun);
		vector<int> max_hit(n);
		vector<int> min_hit(n);
		rep(i,n){
			min_hit[i] = dat[i].F - dat[i].S;
			max_hit[i] = dat[i].F + dat[i].S;
		}


		rep(dir, 2){
			for(int i = dir ? 0 : n-1; i >= 0 && i < n; i = dir ? i + 1 : i - 1){
				int low = min_hit[i];
				int high = max_hit[i];

				max_root->get(low, high, &max_hit[i]);
				min_root->get(low, high, &min_hit[i]);

				max_root->put(dat[i].F, max_hit[i]);
				min_root->put(dat[i].F, min_hit[i]);
			}
		}

		map<int,int> loc_to_pos;
		rep(i, n)
			loc_to_pos[dat[i].F] = i;

		vector<int> res(n);
		rep(i,n){
			map<int,int>::iterator it1 = loc_to_pos.lower_bound(min_hit[i]);
			map<int,int>::iterator it2 = --loc_to_pos.upper_bound(max_hit[i]);
			int ans = it2->S - it1->S + 1;
			res[loc_to_idx[dat[i].F]] = ans;
		}
		rep(i, n){
			if(i) cout << " ";
			cout << res[i];
		}
		cout << endl;
		
	}
}	
