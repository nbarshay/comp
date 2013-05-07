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

template<class T>
ostream& operator<<(ostream& out, vector<T> v){
	out << "[";
	rep(i, sz(v)){
		if(i) cout << ", ";
		out << v[i];
	}
	out << "]";
	return out;
}

//find first copy of s in t, and return index, -1 otherwise
int match(string S, string T){
	vector<int> F(sz(S)+1);	
	int at = 0;
	For(i,2,sz(S)){
		while(at > 0 && S[i-1] != S[at])
			at = F[at];
		if(S[i-1] == S[at])
			F[i] = ++at;
	}

	cout << F << endl;
	
	at = 0;
	rep(i,sz(T)){
		while(at > 0 && S[at] != T[i])
			at = F[at];
		if(S[at] == T[i]){
			at++;
			cout << at << endl;
			if(at == sz(S)){
				return i - sz(S) + 1;
			}
		}
	}
	return -1;
}

int main(){
	while(1){
		string S,T;
		cin >> S >> T;
		cout << match(S,T) << endl;
	}
}	

