#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)

#define F first
#define S second

typedef long long ll;

const ll inf = 1000000000000000005LL;

map<ll,ll> m;

void insert(ll x, ll val){
	map<ll,ll>::iterator after = m.upper_bound(x);
	

	if(after != m.end() && val >= (after->S + (after->F - x)))
		return;
	if(after != m.begin()){
		map<ll,ll>::iterator before = after;
		--before;
		if(val >= (before->S + (x - before->F)))
			return;
	}
	
	m[x] = val;
	map<ll,ll>::iterator it = m.find(x);

	while(true){
		map<ll,ll>::iterator next = it;
		++next;
		if(next == m.end() || next->S < (val + (next->F - x)))
			break;
		m.erase(next);
	}

	while(it != m.begin()){
		map<ll,ll>::iterator prev = it;
		--prev;
		if(prev->S < (val + (x - prev->F)))
			break;
		m.erase(prev);
	}
}

ll clear(ll a, ll b){
	map<ll,ll>::iterator low = m.lower_bound(a);
	map<ll,ll>::iterator high = m.upper_bound(b);

	ll low_val = inf;
	ll high_val = inf;

	for(map<ll,ll>::iterator it = low; it != high; it++){
		low_val = min(low_val, it->S + (it->F - a));
		high_val = min(high_val, it->S + (b - it->F));
	}
	
	m.erase(low, high);
	
	insert(a, low_val);
	insert(b, high_val);
}

ll get(ll at){
	ll res = inf;
	map<ll,ll>::iterator after = m.upper_bound(at);
	if(after != m.end())
		res = min(res, after->S + (after->F - at));
	if(after != m.begin()){
		map<ll,ll>::iterator before = after;
		--before;	
		res = min(res, before->S + (at - before->F));
	}
	return res;
}

int main(){
	ll n, s;
	cin>>n>>s;

	insert(0, 0);
	rep(i,n){
		ll a,b; cin>>a>>b;
		clear(a,b);
	}
	cout << get(s) << endl;
}	
