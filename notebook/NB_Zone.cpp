vector<vector<int> > A;
const int NV = 10000;
int n;
stack<int> st;
int npre = 0;
int low[NV];
int pre[NV];
int Z[NV];
int nz = 0;
void zoneRec(int at, int from){
	low[at] = pre[at] = npre++;
	st.push(at);
	foreach(e, A[at]){
		int to = *e;
		if(to == from) continue;
		if(pre[to] == -1) zoneRec(to, at);
		low[at] = min(low[at], low[to]);
	}
	if(low[at] < pre[at]) return;
	int top = -1;
	while(top != at){
		top = st.top(); st.pop();
		Z[top] = nz;
	}
	nz++;
}
void zone(){
	npre = nz= 0;
	memset(pre,255,sizeof(pre));
	rep(i, n) if(pre[i] == -1) zoneRec(i, -1);
}
