int lvl[MX];
int pr[MX];

int dfs(int v, int p, int sz, int &cent) {
    int sum = 1;
    fx(to, g[v]) {
        if (lvl[to] == -1 && to != p)
            sum += dfs(to, v, sz, cent);
    }
    if ((p == -1 || sum * 2 >= sz) && cent == -1)
        cent = v;
    return sum;
}

void build(int v, int sz, int level = 0, int last = -1) {
    int cent = -1;
    dfs(v, -1, sz, cent);
    pr[cent] = last;
    lvl[cent] = level;
    fx(to, g[cent]) {
        if (lvl[to] == -1)
            build(to, sz / 2, level + 1, cent);
    }
}
