struct mcmf{
    struct edge{
        int to, cost, cap, flow;
        edge() {}
        edge(int _to, int _cap, int _cost) {
            to = _to, cost = _cost, cap = _cap, flow = 0;
        }
        int can() const {
            return cap - flow;
        }
    };
    int n;
    int s, t;
    vector<vector<int>> g;
    vector<edge> edges;
 
    mcmf() {}
 
    mcmf(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        g.assign(n, vector<int>());
        edges = {};
    }
 
    void addEdge(int from, int to, int cap, int cost) {
        g[from].push_back(edges.size());
        edges.push_back({to, cap, cost});
        g[to].push_back(edges.size());
        edges.push_back({from, 0, -cost});
    }
 
    const int INF = 1e9 + 228;
    vector<int> dist;
    queue<int> q;
    vector<bool> used;
    vector<int> par;
 
    bool FB() {
        dist.assign(n, INF);
        par.assign(n, -1);
        used.assign(n, false);
        q.push(s);
        used[s] = true;
        dist[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            used[v] = false;
            for (auto i : g[v]) {
                if (edges[i].can() < 1) continue;
                int to = edges[i].to;
                int cost = edges[i].cost;
                if (dist[to] <= dist[v] + cost) continue;
                dist[to] = dist[v] + cost;
                par[to] = i;
                if (!used[to]) {
                    used[to] = true;
                    q.push(to);
                }
            }
        }
        return dist[t] != INF;
    }
 
    int getMaxFlow(int maxCost) {
        int ans = 0;
        while (FB()) {
            int minCap = INF;
            int v = t;
            while (v != s) {
                mine(minCap, edges[par[v]].can());
                v = edges[par[v] ^ 1].to;
            }
            bool last = minCap * dist[t] > maxCost;
            if (dist[t]) mine(minCap, maxCost / dist[t]);
            if (minCap == 0) break;

            maxCost -= minCap * dist[t];
            ans += minCap;
            v = t;
            while (v != s) {
                edges[par[v]].flow += minCap;
                edges[par[v] ^ 1].flow -= minCap;
                v = edges[par[v] ^ 1].to;
            }
            if (last) break;
        }
        return ans;
    }
};
