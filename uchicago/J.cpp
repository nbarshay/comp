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

const int NEG = 0;
const int AND = 1;
const int OR = 2;
const int VAR = 3;
const int ONE = 4;

#define TWO(x) (1LL<<(x))

int var_nidx=0;
vector<char> idx_to_var;

bool mysort(char a, char b){
	return tolower(a) < tolower(b);
}


struct Node{
	Node* left;
	Node* right;
	int type;
	int var;

	bool should_mem;
	vector<ll> mem_dat;
	bool done;

	Node() : done(false) , should_mem(false) {}

	string toString(){
		stringstream ss;
		ss << "(";
		if(left)
			ss << left->toString();
		if(type == AND)
			ss << "&";
		else if(type == OR)
			ss << "|";
		else if(type == NEG)
			ss << "~";
		else if(type == VAR)
			ss << (char)idx_to_var[var];
		else if(type == ONE)
			ss << "ALL";
		if(right)
			ss << right->toString();
		ss << ")";
		return ss.str();
	}

	vector<ll> eval(){
		if(done){
			return mem_dat;
		}
		vector<ll> dat ((TWO(var_nidx) + 63)/64);
		
		if(type == ONE){
			rep(i, TWO(var_nidx))
				dat[i/64] |= TWO(i%64);
		} else if(type == VAR){
			rep(i, TWO(var_nidx)) if(i & TWO(var))
				dat[i/64] |= TWO(i%64);
		} else if(type == NEG){
			vector<ll> hit = right->eval();
			rep(i, sz(dat))
				dat[i] = ~hit[i];
		} else if(type == OR){
			vector<ll> hit1 = left->eval();
			vector<ll> hit2 = right->eval();
			rep(i, sz(dat))
				dat[i] = hit1[i] | hit2[i];
		} else if(type == AND){
			vector<ll> hit1 = left->eval();
			vector<ll> hit2 = right->eval();
			rep(i, sz(dat))
				dat[i] = hit1[i] & hit2[i];
		}
		
		if(should_mem){
			done = true;
			mem_dat = dat;
		}

		return dat;
	}

	string show(){
		eval();
		assert(done);

		int yes = 0, no = 0;
		int cnt = 0;
		rep(i, sz(mem_dat)) rep(j, 64) if(mem_dat[i] & TWO(j)){
			int idx = i*64 + j;
			yes |= idx;
			no |= ~idx;
			cnt++;
		}
		if(cnt){
			string res;
			rep(i, var_nidx){
				bool y = yes & TWO(i);
				bool n = no & TWO(i);
				if(y && !n)
					res += toupper(idx_to_var[i]);
				if(!y && n)
					res += tolower(idx_to_var[i]);
			}
			sort(res.begin(), res.end(), mysort);
			return res;
		} else{
			return "unreachable";
		}
	}
};

vector<Node*> check;

map<char,Node*> var_to_idx;

Node* build_var(char c){
	if(!var_to_idx.count(c)){
		int id = var_nidx++;
		idx_to_var.pb(c);

		Node* node = new Node();
		node->left = node->right = NULL;
		node->type = VAR;
		node->var = id;
		node->should_mem = true;

		var_to_idx[c] = node;
	}

	return var_to_idx[c];
}

Node* build_and(Node* a, Node* b){
	Node* ret = new Node();
	ret->type = AND;
	ret->left = a;
	ret->right = b;
	ret->should_mem = true;
	return ret;
}

Node* build_neg(Node* a){
	Node* ret = new Node();
	ret->type = NEG;
	ret->left = NULL;
	ret->right = a;
	ret->should_mem = true;
	return ret;
}

int get_type(char c){
	if(c == '&')
		return AND;
	else if(c == '|')
		return OR;
	else if(c == '~')
		return NEG;
	else
		return -1;
}

Node* build(string& s, int a, int b){
	//cout << "BUILD: " << s.substr(a, b-a) << endl;
	
	if(a+1 == b){
		assert(s[a] >= 'A' && s[a] <= 'Z');
		return build_var(s[a]);
	}

	int type = -1;
	int loc = -1;
	int cnt = 0;
	For(i,a,b){
		if(s[i] == '(')
			cnt++;
		else if(s[i] == ')')
			cnt--;
		else if(cnt == 0){
			int t = get_type(s[i]);
			if(t > type){
				type = t;
				loc = i;
			}
		}
	}
	if(type == -1){
		assert(s[a] == '(' && s[b-1] == ')');
		return build(s, a+1,b-1);
	}
	Node* node = new Node();
	node->type = type;
	if(type == NEG){
		assert(loc == a);
		node->left = NULL;
		node->right = build(s, a+1, b);
	} else{
		node->left = build(s,a,loc);
		node->right = build(s,loc+1,b);
	}

	return node;
}

void parse(vector<string>& v, int a, int b, Node* parent){
	/*cout << "PARSE: ";
	For(i,a,b)
		cout << v[i] << " ";
	cout << endl;*/

	int at = a;
	while(at < b){
		if(v[at] == "checkpoint"){
			check.pb(parent);
			at++;
		} else if(v[at] == "if"){
			int if_loc = at;
			int else_loc = -1;
			int fi_loc = -1;
			int cnt = 0;
			For(i,at,b){
				if(v[i] == "if"){
					cnt++;
				} else if(v[i] == "fi"){
					cnt--;
					if(cnt == 0){
						fi_loc = i;
						break;
					}
				} else if(v[i] == "else" && cnt == 1){
					assert(else_loc == -1);
					else_loc = i;
				}
			}
			assert(fi_loc >= 0);

			if(else_loc == -1)
				else_loc = fi_loc;

			string str = v[if_loc+1];
			Node* state = build(str,0,sz(str));
			state->should_mem = true;
			
			parse(v, if_loc + 3, else_loc, build_and(parent, state));

			if(else_loc != fi_loc){
				parse(v, else_loc+1, fi_loc, build_and(parent, build_neg(state)));
			}

			at = fi_loc + 1;
		} else{
			assert(0);
		}
	}
}


int main(){
	vector<string> v;
	string cur_s;
	while(cin >> cur_s){
		v.pb(cur_s);
	}

	Node* all = new Node();
	all->type = ONE;
	all->right = all->left = NULL;
	all->should_mem = true;

	parse(v, 0, sz(v), all);


	rep(i, sz(check)){
		//cout << check[i]->toString()<<endl;;
		cout << ">";
		cout << check[i]->show();
		cout << endl;
	}
}

