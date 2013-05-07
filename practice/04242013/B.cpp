#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

#define For(i, a, b) for(int (i) =  int(a); i < int(b); ++i)
#define rep(x, n) For(x,0,n)

#define sz(a) int((a).size())


vector<int> F;
string S;

void init(){
	F = vector<int>(sz(S)+1);	
	int at = 0;
	For(i,2,sz(S)){
		while(at > 0 && S[i-1] != S[at])
			at = F[at];
		if(S[i-1] == S[at])
			F[i] = ++at;
	}
}

//find first copy of s in t, and return index, -1 otherwise
list<char>::iterator match(list<char>::iterator it, list<char>::iterator end){
	int at = 0;
	for( ; it != end; ++it){
		while(at > 0 && S[at] != *it)
			at = F[at];
		if(S[at] == *it){
			at++;
			if(at == sz(S)){
				rep(i, sz(S)-1)
					it--;
				return it;
			}
		}
	}
	return end;
}

int main(){
	int n;
	while(cin >> n >> S){
		init();
		string garbage; getline(cin, garbage);
		rep(i,n){
			string T; getline(cin, T);
			list<char> lst;
			for(char& c : T)
				lst.push_back(c);

			list<char>::iterator at = lst.begin();
			while(1){
				at = match(at, lst.end());
				if(at == lst.end())
					break;
				rep(i, sz(S))
					at = lst.erase(at);
				rep(i, sz(S)) if(at != lst.begin())
					--at;
			}

			for(char& c : lst)
				cout << c;
			cout << endl;
		}
	}
}	
