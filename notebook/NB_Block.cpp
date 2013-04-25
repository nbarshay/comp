vector<vector<Edge*> > A;
const int NV = 10000;
int n;
stack<Edge*> st;
int npre = 0;
int low[NV];
int pre[NV];
int nblock = 0;
void blockRec(int at, int from){
	low[at] = pre[at] = npre++;
	foreach(e, A[at]){
		int to = (*e)->to(at);
		if(to == from) continue;
		if(pre[to]>=0){
			if(pre[to] < pre[at]) st.push(*e);
			setmin(low[at], pre[to]);
		} else{
			st.push(*e);
			blockRec(to, at);
			setmin(low[at], low[to]);
			if(low[to] >= pre[at]){
				Edge* top = NULL;
				while(top != *e){
					top = st.top(); st.pop();
					top->block = nblock;
				}
				nblock++;
			}
		}
	}
}
void block(){
	npre = nblock = 0;
	memset(pre,255,sizeof(pre));
	rep(i, n) if(pre[i] == -1) blockRec(i, -1);
}
