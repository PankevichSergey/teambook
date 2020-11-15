struct edge {
    int to;
    int f;
    int c;
    edge (int aa, int bb, int cc) {
        to = aa;
        f = bb;
        c = cc;
    }
};

int K;
int s, t;
int n, m;
vector<edge> edges;
vi g[MX];
int dist[MX];

bool bfs() {
    queue<int> q;
    q.push(s); 
    fill(dist, dist + n, INF);
    dist[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        fx(id, g[v]) {
            int to = edges[id].to;
            int can = edges[id].c - edges[id].f;
            if (can < K || dist[to] != INF) continue;
            dist[to] = dist[v] + 1;
            if (to == t)
                return true;
            q.push(to);
        }
    }
    return false;
}

int it[MX];

int dfs(int v, int mn = INF) {
    if (v == t)
        return mn;
    while (it[v] != siz(g[v])) {
        int id = g[v][it[v]];
        int to = edges[id].to;
        int can = edges[id].c - edges[id].f;
        if (can >= K && dist[to] == dist[v] + 1) {
            int res = dfs(to, min(mn, can));
            if (res) {
                edges[id].f += res;
                edges[id^1].f -= res;
                return res;
            }
        }
        ++it[v];
    }
    return 0;
}

int maxflow() {
    int flow = 0;
    K = 1 << 30;
    while (K) {
        while (bfs()) {
            memset(it, 0, sizeof(int) * n);
            int delta;
            while (delta = dfs(s))
                flow += delta;
        }
        K >>= 1;
    }
    return flow;
}
