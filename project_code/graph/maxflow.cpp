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
    vector<edge> e;
    vector<vector<int>> g;
    int n;
    int s;
    int t;
    dinic(int _n) {
        n = _n + 2;
        s = n - 1;
        t = n - 2;
        g.resize(n);
    }
    void add_edge(int a, int b, int cap) {
        g[a].push_back(e.size());
        e.push_back(edge(b, cap, 0));
        g[b].push_back(e.size());
        e.push_back(edge(a, 0, 0));
    }
    void flow(int id, int x) {
        e[id].flow += x;
        e[id ^ 1].flow -= x;
    }
    const int INF = 1e9 + 50;
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
                if (e[id].can()) {
                    int to = e[id].to;
                    if (dist[to] == INF) {
                        dist[to] = dist[v] + 1;
                        q.push(to);
                    }
                }
            }
        }
        return dist[t] < INF;
    }
    vector<int> it;
    int dfs(int v, int curmin) {
        if (v == t) return curmin;
        while (it[v] < g[v].size()) {
            int id = g[v][it[v]];
            int to = e[id].to;
            if (e[id].can() && dist[to] == dist[v] + 1) {
                int res = dfs(to, min(curmin, e[id].can()));
                if (res) {
                    flow(id, res);
                    return res;
                }
            } 
            ++it[v];
        }
        return 0;
    }
    int maxflow() {
        int res = 0;
        while (bfs()) {
            int delta;
            it.assign(n, 0);
            while (delta = dfs(s, INF)) {
                res += delta;
            } 
        }
        return res;
    }
};
