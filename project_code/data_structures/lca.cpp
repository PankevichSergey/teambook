int timer = 0;
int tin[N];
int tout[N];
int depth[N];
int sz[N];
int up[N][PW];


void init_dfs(int v, int pr) {
    tin[v] = timer++;
    sz[v] = 1;
    up[v][0] = pr;
    for (int i = 1; i < PW; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to != pr) {
            depth[to] = depth[v] + 1;
            init_dfs(to, v);
            sz[v] += sz[to];
        }
    }
    tout[v] = timer;
}


int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int delta = depth[a] - depth[b];
    for (int i = PW - 1; i >= 0; --i) {
        if ((delta >> i) & 1) {
            a = up[a][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = PW - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}
