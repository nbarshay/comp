#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <queue>
using namespace std;

#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)

#define sz(a) int((a).size())
#define mp make_pair
#define F first
#define S second
#define pb push_back

typedef pair<int, int> PII;

typedef long long ll;
typedef long double ld;

vector<vector<pair<ll,ll> > > adj;

vector<ll> doit(ll base){
	vector<ll> D(sz(adj) ,-1);
	priority_queue<PII , vector<PII>, greater<PII> > pq;

	D[base] = 0;
	pq.push( mp(D[base], base));
	while(!pq.empty()){
		ll hit = pq.top().F;
		ll at = pq.top().S;
		pq.pop();
		if(hit > D[at])
			continue;
		rep(i, sz(adj[at])){
			ll to = adj[at][i].F;
			ll cost = D[at] + adj[at][i].S;
			if(cost < D[to] || D[to] == -1){
				D[to] = cost;
				pq.push(mp(D[to], to));
			}
		}
	}
	return D;
}

int main(){
	ll np; cin >> np;
	rep(tp,np){
		ll n,m; cin>>n>>m;
		adj = vector<vector<pair<ll,ll> > >(n);
		rep(i,m){
			ll a,b,c; cin>>a>>b>>c;
			a--; b--;
			adj[a].pb(mp(b,c));
			adj[b].pb(mp(a,c));
		}
		vector<ll> XR = doit(0);
		vector<ll> YR = doit(1);

		vector<ll> X(n);
		vector<ll> Y(n);
		rep(i,n){
			X[i] = XR[i] + YR[i];
			Y[i] = XR[i] - YR[i];
		}

		vector<ll> XS = X, YS = Y;
		sort(XS.begin(), XS.end());
		sort(YS.begin(), YS.end());

		ll cx = XS[sz(XS)/2];
		ll cy = YS[sz(YS)/2];

		ld ans = 0.0;
		rep(i, n){
			ans += abs(X[i] - cx);
			ans += abs(Y[i] - cy);
		}

		cout << setprecision(10) << fixed << (ans / (2.0*n)) << endl;
		
	}
}	
