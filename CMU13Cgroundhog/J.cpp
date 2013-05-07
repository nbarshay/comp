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

vector<int> A;
vector<int> st;
vector<int> pos;

void incr(){
	for(int i = sz(st)-1; i >= 1; i--){
		pos[i]++;
		if(st[i] < A[i-1] - 2){
			st[i]++;
			break;
		} else{
			st[i] = 0;
		}
	}
}

void decr(){
	for(int i = sz(st)-1; i >= 1; i--){
		pos[i]--;
		if(st[i] > 0){
			st[i]--;
			break;
		} else {
			st[i] = A[i-1] - 2;
		}
	}
}

int inf = 1000000000;

int main(){
	string s;
	cin >> s;
	A = vector<int>(sz(s));
	rep(i, sz(s))
		A[i] = s[i] - '0';

	A.pb(0);

	pos = vector<int>(sz(A), 0);

	cin >> s;
	vector<int> C(sz(s));
	rep(i, sz(s))
		C[i] = s[i] - '0';

	int edge_in = A[1] + 2;
	st.pb(0);
	st.pb(0);

	vector<int> last(sz(A), inf);
	int ans1 = 0, ans2 = 0;

	rep(i,sz(C) - 1){
		//cout << st << endl;
		int level = sz(st) - 1;
		bool double_down = (st.back() == 0) && level != 1;
		int mod = double_down ? A[level] + 4 : A[level] + 3;
		int edge = (edge_in + C[i]) % mod;
		//cout << edge_in << " " << edge << endl;
		if(edge == 0){
			ans1--;
			//cout << "LEFT ROT" << endl;
			decr();
			edge_in = A[level] + 1;	
		}else if(edge == A[level] + 1){
			ans2--;
			//cout << "RIGHT ROT" << endl;
			incr();			
			edge_in = 0;
		}
		else if(edge >= 1 && edge <= A[level]){
			//cout << "OUT" << endl;
			last[level] = pos[level];
			int jump = edge - 1;	
			if(jump < A[level] -1){
				st.pb(jump);
				edge_in = A[level+1] + 2;
			} else{
				incr();
				st.pb(0);
				edge_in = A[level+1] + 3;
			}
		} else{ 
			if(edge == A[level] + 2){
				//cout << "DOWN" << endl;
				edge_in = st.back() + 1;
				st.pop_back();
			} else if(edge == A[level] + 3){
				//cout << "DOWN + DECR" << endl;
				edge_in = A[level-1] ;
				st.pop_back();
				decr();
			}

			if(level != 1){
				int cur_pos = pos[level-1];
				int last_pos = last[level-1];
				assert(last_pos != inf);
				last[level-1] = inf;
				//printf("proc: %d %d %d\n", level-1, cur_pos, last_pos);
				int in = abs(cur_pos - last_pos) - 1;
				int out = abs(cur_pos - last_pos) + 1;
				if(cur_pos > last_pos){
					ans1 += in;
					ans2 -= out;
				} else{
					ans1 -= out;
					ans2 += in;
				}
			}
		}
	}
	assert(sz(st) == 1);
	//cout << st << endl;
	//cout << ans1 << " " << ans2 << endl;
	cout << max(ans1, ans2) << endl;
}	
