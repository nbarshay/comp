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
	return out;
}

long long roundUp(long long a, long long b){
	return (a+b-1)/b;
}

int len(vector<int>& a){
	int ans = sz(a);
	foreach(it, a)
		ans += *it;
	return ans;
}

bool compare(vector<int> a, vector<int> b){
	if(len(a) != len(b))
		return len(a) < len(b);
	
	int pta = sz(a)-1, ptb = sz(b)-1;
	while(1){
		if(a[pta] != b[ptb])
			return a[pta] > b[ptb];
		pta--; ptb--;
		if(pta < 0)
			return true;
		if(ptb < 0)
			return false;
	}
}

void show(vector<int> a){
	vector<pair<char,int> > vec;
	for(int i = sz(a)-1; i >= 0; i--){
		int num = a[i];
		if(num == 0){
			if(i != 0){
				if(sz(vec))
					vec.back().S++;
				else
					vec.pb(mp('M', 1));
			}
		} else{
			vec.pb(mp('A', num));
			if(i != 0){
				vec.pb(mp('M', 1));
			}
		}
	}
	if(sz(vec) ==0 ){
		cout << " empty";
	}else{
		foreach(it, vec){
			cout << " " << it->S << it->F;
		}
	}

}

int main(){
int cas=0;
while(1){
	int A, M, P, Q, R, S; cin >> A >> M >> P >> Q >> R >> S;
	if(A == 0)
		break;
	vector<vector<int> > opts;
	for(int nmul = 0; ; nmul++){
		if(M == 1 && nmul > 0)
			break;
		vector<long long> pow(nmul+1);
		pow[0] = 1;
		bool bad = false;
		rep(i, nmul){
			long long temp = pow[i]*M;
			if(temp*Q > S){
				bad = true;
				break;
			}
			pow[i+1] = temp;
		}
		if(bad)
			break;

		long long shift_low = max(0LL, R - P*pow[nmul]);
		long long shift_high = S - Q*pow[nmul];
		long long shift = 0;
		vector<int> dig(nmul+1);	
		for(int i = nmul; i>=0; i--){
			long long low_mul = roundUp(shift_low - shift, (pow[i]*A));
			long long high_mul = (shift_high - shift)/(pow[i]*A);
			long long mul = min(low_mul, high_mul);
			if(mul > 0){
				dig[i] = mul;	
				shift += mul*(pow[i]*A);
			}
		}
		if(P*pow[nmul] + shift >= R && Q*pow[nmul] + shift <= S)
			opts.pb(dig);
	}
	printf("Case %d:", ++cas);
	if(sz(opts) == 0){
		cout << " impossible" << endl;
	} else{
		sort(opts.begin(), opts.end(), compare);
		show(opts[0]);
		cout << endl;
	}
}

}	
