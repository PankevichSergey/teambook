struct dinic {
    struct edge {
        int to;
        int cap;
        int flow;
        edge(int _to, int _cap, int _flow): to(_to), cap(_cap), flow(_flow) {}
        int can() {
            return cap - flow;
        }
    };
    
    int n;
    int s;
    int t;
    vector<vector<int>> g;
    vector<edge> e;
    dinic() {}
    dinic(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        g.resize(n);
    }
    void add_edge(int a, int b, int cap) {
        g[a].pb(e.size());
        e.pb(edge(b, cap, 0));
        g[b].pb(e.size());
        e.pb(edge(a, 0, 0));
    }
    void push(int id, int flow) {
        e[id].flow += flow;
        e[id ^ 1].flow -= flow;
    } 

    const int INF = 1e9 + 228;
    vector<int> dist;
    bool bfs() {
        dist.assign(n, INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int v = q.front();        
            q.pop();
            for (int id : g[v]) {
                if (e[id].can() && dist[e[id].to] == INF) {
                    dist[e[id].to] = dist[v] + 1;
                    q.push(e[id].to);
                }

            }
        }
        return dist[t] < INF;
    }
    vector<int> ptr;
    int dfs(int v, int curmin) {
        if (v == t) return curmin;
        while (ptr[v] < g[v].size()) {
            int id = g[v][ptr[v]];
            int to = e[id].to;
            if (e[id].can() && dist[to] == dist[v] + 1) {
                int can = dfs(to, min(curmin, e[id].can()));
                if (can) {
                    push(id, can);
                    return can;
                }
            }
            ++ptr[v];
        }
        return 0;
    }
    int maxflow() {
        int flow = 0;
        while (bfs()) {
            ptr.assign(n, 0);
            int delta;
            while (delta = dfs(s, INF)) {
                flow += delta;                
            }            
        }       
        return flow;
    }
};
