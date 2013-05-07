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

struct Node{
	int a,b;
	Node *left, *right;
	int cnt;
	Node (int _a, int _b){
		a = _a, b = _b;	
		cnt = 0;
		if(a == b){
			left = right = NULL;
		} else{
			int m = (a+b+1)/2;
			left = new Node(a, m-1);
			right = new Node(m,b);
		}
	}

	void insert(int head, int tail){
		if(head >= a && head <= b && tail >= a && tail <= b){
			cnt++;
			if(left && right){
				left->insert(head, tail);
				right->insert(head, tail);
			}
		}
	}

	int get(int low, int high){
		if(low <= a && high >= b){
			return cnt;
		} else if(high < a || low > b){
			return 0;
		} else{

		}
	}
}

int main(){
	int N,M; cin>>N>>M;
	vector<int> perm(N);
	vector<int> loc(N+1);
	rep(i,N){
		cin >> perm[i];
		loc[perm[i]] = i;
	}
	int res = 0;
	For(i,1,N+1){
		for(int k = i; k <= N; k+= i)
			res++;
	}
	cout << res << endl;
		
			
}	
