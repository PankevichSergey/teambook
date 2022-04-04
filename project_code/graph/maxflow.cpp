template<typename T>
struct Dinic {
    struct edge {
        int to;
        T cap;
        T flow;
        edge(int _to, T _cap, T _flow): to(_to), cap(_cap), flow(_flow) {}
        T can() {
            return cap - flow;
        }
    };
    vector<edge> e;
    vector<vector<int>> g;
    vector<T> dist;

    int n;
    int s; // source
    int t; // sink

    Dinic(int _n) { // n vertices, source and sink are added
        n = _n + 2;
        s = n - 1;
        t = n - 2;
        g.resize(n);
        dist.resize(n);
    }
    Dinic(int _n, int _s, int _t) { // n vertices, source and sink are given
        s = _s;
        t = _t;
        n = _n;
        g.resize(n);
        dist.resize(n);
    }

    void add_edge(int a, int b, T cap) {
        g[a].push_back(e.size());
        e.push_back(edge(b, cap, 0));
        g[b].push_back(e.size());
        e.push_back(edge(a, 0, 0));
    }
    void flow(int id, T x) {
        e[id].flow += x;
        e[id ^ 1].flow -= x;
    }
    const T INF = numeric_limits<T>::max() / 2 - 2;

    queue<int> q;

    bool bfs() {
        q = {};
        fill(dist.begin(), dist.begin() + n, INF);
        dist[s] = 0;
        q.push(s);
        while (q.size() && dist[t] == INF) {
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
    T dfs(int v, T curmin) {
        if (v == t) return curmin;
        while (it[v] < g[v].size()) {
            int id = g[v][it[v]];
            int to = e[id].to;
            if (e[id].can() && dist[to] == dist[v] + 1) {
                T res = dfs(to, min(curmin, e[id].can()));
                if (res) {
                    flow(id, res);
                    return res;
                }
            }
            ++it[v];
        }
        return 0;
    }
    T maxflow() {
        T res = 0;
        while (bfs()) {
            T delta;
            it.assign(n, 0);
            while (delta = dfs(s, INF)) {
                res += delta;
            }
        }
        return res;
    }
};
