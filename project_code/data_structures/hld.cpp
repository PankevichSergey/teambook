int n;
vi g[MX];
int sz[MX], pr[MX];

void dfs(int v, int p) {
    pr[v] = p;
    sz[v] = 1;
    int mx = 0;
    fi(0, siz(g[v])) {
        int to = g[v][i];
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
        if (sz[to] > mx) {
            mx = sz[to];
            swap(g[v][0], g[v][i]);
        }
    }
}

int tin[MX], tout[MX], t = 0;
int up[MX];

void build(int v, int p) {
    tin[v] = t++;
    fx(to, g[v]) {
        if (to == p) continue;
        up[to] = (to == g[v][0] ? up[v] : to);
        build(to, v);
    }
    tout[v] = t;
}

bool is_anc(int a, int b) {
    return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

int ascend(int ja, int b, int &ans) {
    while (!is_anc(up[ja], b)) {
        ans = max(ans, get(1, tin[up[ja]], tin[ja] + 1, 0, n));
        ja = pr[up[ja]];
    }
    return ja;
}

int req(int a, int b) {
    int ans = 0;
    int ja = ascend(a, b, ans);
    int jb = ascend(b, a, ans);
    if (is_anc(jb, ja))
        swap(ja, jb);
    return max(ans, get(1, tin[ja], tin[jb] + 1, 0, n));
}
