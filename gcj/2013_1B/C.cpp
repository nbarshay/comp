#include <iostream>
#include <unordered_map>
#include <fstream>
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

}

void setmin(int& a, int b){
	if(a == -1 || b < a)
		a = b;
}

struct Node{
	vector<Node*> child;
	bool word;
	Node() : child(26, (Node*)NULL), word(false){
	}
	void insert(string& s, int idx){
		if(idx == sz(s)){
			word = true;
			return;
		} else{
			int c = s[idx] - 'a';
			if(child[c] == NULL)
				child[c] = new Node();
			child[c]->insert(s, idx+1);
		}
	}
	void read(string& s, int idx, int used, int wait, int* res, int& base){
		assert(used <= 2);
		if(idx == sz(s)){
			if(word)
				setmin(res[wait], used + base);
		} else{
			int c = s[idx] - 'a';

			if(child[c] != NULL)
				child[c]->read(s, idx+1, used, max(wait-1,0), res,base);

			if(wait == 0){
				rep(i, 26) if(child[i] != NULL)
					child[i]->read(s, idx+1, used+1, 4, res,base);
			}
		}
	}
};

const int MAXN = 4005;
int DP[MAXN][5];
Node* root;

int main(){
	ifstream fin("garbled_email_dictionary.txt");
	//ifstream fin("dict.txt");
	string s;
	int idx = 0;
	root = new Node();
	int res = 0;
	while(fin >> s){
		root->insert(s,0);
		res = max(res, sz(s));
	}
	
	int cases; cin>>cases;
	rep(cas, cases){
		memset(DP, -1, sizeof(DP));
		string str; cin>>str;
		int N = sz(str);
		DP[0][0] = 0;
		rep(i, N) rep(k, 5) if(DP[i][k] >= 0){
			For(len,1,11) if(i + len <= N){
				string query = str.substr(i, len);
				root->read(query,0,0,k,DP[i + len], DP[i][k]);
			}
		}
		assert(DP[N] >= 0);
		int res = -1;
		rep(i,5) if(DP[N][i] >= 0)
			setmin(res, DP[N][i]);
		printf("Case #%d: %d\n", cas+1, res);
	}
}	
