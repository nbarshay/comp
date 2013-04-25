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

typedef long long ll;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef vector<string> VS;
typedef pair<int, int> PI;

typedef long long ll;

struct Node{
	ll a,b;
	ll sum;
	ll cnt;
	Node* left;
	Node* right;

	Node(vector<ll>& x,ll low, ll high){
		a = x[low];
		b = x[high-1];

		if(low + 1 == high){
			left = right = NULL;
			sum = a;
			cnt = 1;
		} else{
			ll piv = (low+high)/2;
			left = new Node(x, low, piv);
			right = new Node(x, piv, high);
			sum = left->sum + right->sum;
			cnt = left->cnt + right->cnt;
		}
	}
	void erase(ll at){
		if(at < a || at > b)
			return;

		cnt--;
		sum -= at;

		if(left && right){
			right->erase(at);
			left->erase(at);
		}
	}
	void get(ll low, ll high, ll& r_sum, ll& r_cnt){
		if(high < a || low > b){
			
		} else if(low <= a && high >= b){
			r_sum += sum;
			r_cnt += cnt;
		} else{
			right->get(low, high, r_sum, r_cnt);
			left->get(low, high, r_sum, r_cnt);
		}
	}
};

int main(){
	vector<ll> x;
	vector<pair<ll,ll> > v;	//<volume, position>
	ll n; cin>>n;
	rep(i,n){
		ll vol, xx;
		cin >> vol >> xx;
		x.pb(xx);
		v.pb(mp(vol, xx));
	}
	sort(v.begin(), v.end(), greater<pair<ll,ll> >());
	sort(x.begin(), x.end());

	Node* root = new Node(x,0,sz(x));

	ll res = 0;
	foreach(it, v){
		ll vol = it->F, pos = it->S;

		ll lsum=0, lcnt=0;
		root->get(0, pos-1, lsum, lcnt);
		ll sum_left = lcnt*pos - lsum;

		ll rsum = 0, rcnt = 0;
		root->get(pos+1, 20001, rsum, rcnt);
		ll sum_right = rsum - rcnt*pos;

		res += (sum_left + sum_right) * vol;

		root->erase(pos);
	}

	cout << res << endl;
}

