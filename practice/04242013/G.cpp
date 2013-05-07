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

}

struct Card{
	int rank;
	int suite;
	bool operator<(const Card& in) const{
		return rank > in.rank;
	}
	
	Card(string s){
		char r = s[0];
		if(r >= '2' && r <= '9')
			rank = r - '2';
		else if(r == 'X')
			rank = 8;
		else if(r == 'J')
			rank = 9;
		else if(r == 'Q')
			rank = 10;
		else if(r=='K')
			rank = 11;
		else if(r=='A')
			rank = 12;
		else
			assert(false);

		char c = s[1];
		if(c == 'c')
			suite = 0;
		else if(c == 'd')
			suite = 1;
		else if(c == 'h')
			suite = 2;
		else if(c == 's')
			suite = 3;
		else
			assert(false);
	}
};

bool CardComp(const Card& a, const Card& b){
	if(a.rank != b.rank)
		return a.rank < b.rank;
	else
		return a.suite < b.suite;
}

struct HandComp{
	bool operator() (const vector<Card>& a, const vector<Card>& b) const{
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), CardComp);
	}
};

ostream& operator<<(ostream& out, Card c){
	out << "(" << c.rank << ", " << c.suite << ")";
	return out;
}

const int ACE = 12;

int RF = 0;
int PO = 1;
int FH = 2;
int FL = 3;
int ST = 4;
int TH = 5;
int TP = 6;
int PA = 7;
int ON = 8;


map<vector<Card>, pair<int, pair<vector<Card> ,vector<Card> > >, HandComp> mem;

int get_type(vector<Card> v, vector<Card>& in, vector<Card>& out){
	if(mem.count(v)){
		in = mem[v].S.F; out = mem[v].S.S;
		return mem[v].F;
	}

	in.clear();
	out.clear();

	vector<int> got(ACE+1, 0);
	vector<vector<Card> > gots(ACE+1);
	foreach(it, v){
		got[it->rank]++;
		gots[it->rank].pb(*it);
	}

	vector<Card> straight_vec;

	bool straight = false;
	for(int i = 0; i <= ACE; i++){
		if(i > ACE - 4 && i != ACE)
			continue;
		bool ok = true;
		vector<Card> vec;
		rep(k, 5){
			int idx = (i+k)%sz(got);
			if(!got[idx])
				ok = false;
			else
				vec.pb(gots[idx][0]);
		}
		if(ok){
			straight = true;
			straight_vec = vec;
		}
	}

	set<int> suites;
	foreach(it, v)
		suites.insert(it->suite);


	if(straight && sz(suites) == 1){
		in = straight_vec;
		
		mem[v] = mp(RF, mp(in, out));

		return RF;
	}

	rep(i, sz(got)) if(got[i] == 4){
		foreach(it, v){
			if(it->rank == i)
				in.pb(*it);
			else
				out.pb(*it);
		}

		mem[v] = mp(PO, mp(in, out));
		return PO;
	}

	rep(i, sz(got)) rep(k, sz(got)) if(i!=k) if(got[i] == 3 && got[k] == 2){
		foreach(it, v){
			if(it->rank == i)
				in.pb(*it);
			else
				out.pb(*it);
		}

		mem[v] = mp(FH, mp(in, out));
		return FH;
	}

	if(sz(suites) == 1){
		foreach(it, v)
			in.pb(*it);

		mem[v] = mp(FL, mp(in, out));
		return FL;
	}

	if(straight){
		in = straight_vec;

		mem[v] = mp(ST, mp(in, out));
		return ST;
	}

	rep(i, sz(got)) if(got[i] == 3){
		foreach(it, v){
			if(it->rank == i)
				in.pb(*it);
			else
				out.pb(*it);
		}

		mem[v] = mp(TH, mp(in, out));
		return TH;
	}

	rep(i, sz(got)) rep(k, sz(got)) if(i != k) if(got[i] == 2 && got[k] == 2){
		foreach(it, v){
			if(it->rank == i || it->rank == k)
				in.pb(*it);
			else
				out.pb(*it);
		}

		mem[v] = mp(TP, mp(in, out));
		return TP;
	}

	rep(i, sz(got))  if(got[i] == 2){
		foreach(it, v){
			if(it->rank == i)
				in.pb(*it);
			else
				out.pb(*it);
		}

		mem[v] = mp(PA, mp(in, out));
		return PA;
	}

	foreach(it, v)
		out.pb(*it);

	mem[v] = mp(ON, mp(in, out));
	return ON;
}
bool comp(vector<Card> hand_a, vector<Card> hand_b){
	vector<Card> in_a, out_a, in_b, out_b;
	int type_a = get_type(hand_a, in_a, out_a);
	int type_b = get_type(hand_b, in_b, out_b);
	if(type_a < type_b){
		return true;
	} else if(type_b < type_a){
		return false;
	}

	if(type_a == FH){
		return in_a[0] < in_b[0];
	}

	if(type_a == ST || type_a == RF){
		int low_ace_a = (in_a[0].rank == ACE) ? '1' : '0';
		int low_ace_b = (in_b[0].rank == ACE) ? '1' : '0';
		if(low_ace_a < low_ace_b)
			return true;
		else if(low_ace_b < low_ace_a) 
			return false;
	}

	sort(in_a.begin(), in_a.end());
	sort(in_b.begin(), in_b.end());
	sort(out_a.begin(), out_a.end());
	sort(out_b.begin(), out_b.end());
			
	if(in_a < in_b)
		return true;
	if(in_b < in_a)
		return false;



	if(out_a < out_b)
		return true;
	if(out_b < out_a)
		return false;

	return false;
}

bool comp2(pair<vector<Card>,int> a, pair<vector<Card>, int> b){
	if(comp(a.F,b.F))
		return true;

	if(comp(b.F, a.F))
		return false;

	if(a.S < b.S)
		return true;

	return false;
}




vector<Card> get_best(vector<Card> hand, vector<Card> shared){
	vector<Card> all;
	foreach(it, hand)
		all.pb(*it);
	foreach(it, shared)
		all.pb(*it);

	assert(sz(all) == 7);

	vector<Card> best = shared;
	rep(a, 7) For(b,a+1,7) For(c,b+1,7) For(d,c+1, 7) For(e, d+1, 7){
		vector<Card> act;
		act.pb(all[a]); act.pb(all[b]); act.pb(all[c]); act.pb(all[d]); act.pb(all[e]);
		if(comp(act, best))
			best = act;
	}

	return best;
}


int main(){
	int n;
	while(cin >> n){
		vector<Card> shared;
		rep(i,5){
			string s; cin>>s;
			shared.pb(Card(s));
		}
		vector<pair<vector<Card>,int> > best;
		rep(i,n){
			vector<Card> me;
			rep(k,2){
				string s; cin>>s;
				me.pb(Card(s));
			}
			best.pb(mp(get_best(me, shared), i));
		}

		sort(best.begin(), best.end(), comp2);
		cout << best[0].S+1;

		For(i,1,n){
			if(!comp(best[0].F, best[i].F))
				cout << " " << best[i].S+1;
		}
		cout << endl;
	}
	/*
while(1){
	cout << endl;
	vector<Card> v;
	rep(i, 5){
		string s; cin>>s;
		cout << s << " ";
		v.pb(Card(s));
	}

	cout << endl;
	cout << v << endl;
	vector<Card> in, out;
	int type = get_type(v, in, out);
	sort(in.begin(), in.end());
	sort(out.begin(), out.end());
	cout << type << " " << in << " " << out << endl;
}
*/
/*
while(1){
	string bla; cin>>bla;
	if(bla == "END")
		break;

	vector<Card> v1;
	rep(i, 5){
		string s; cin>>s;
		cout << s << " ";
		v1.pb(Card(s));
	}
	cout << endl;

	vector<Card> v2;
	rep(i, 5){
		string s; cin>>s;
		cout << s << " ";
		v2.pb(Card(s));
	}
	cout << endl;

	cout << v1 << " " << v2 << endl;

	cout << comp(v1, v2) << " " << comp(v2,v1) << endl;
}
*/

}	
