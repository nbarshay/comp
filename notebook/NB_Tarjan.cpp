#define NV 100000
int n;
Vvi A;		//adjacency matrix
int nsc;  // number of scc
int sc[NV];  // holds scc assignment
stack<int> st;
int npre;
int pre[NV];
int low[NV];
void scc(int at){
        low[at]=pre[at]=npre++;
        st.push(at);
        foreach(e, A[at]){
                if(pre[*e] == -1) scc(*e);
                low[at] = min(low[at], low[*e]);
        }
        if(low[at] < pre[at]) return;
        int top=-1;
        while(top!=at){
                top=st.top(); st.pop();
        sc[top]=nsc;
                low[top]=NV;
        }
    nsc++;
}
void tarjan(){
    memset(pre,255,sizeof(pre));
    nsc = npre = 0;
    rep(i, n) if(pre[i]==-1) scc(i);
}
