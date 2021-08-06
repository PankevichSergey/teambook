struct dsu {
    vector<int> pr;
    vector<int> sz;
    dsu(int n) {
        pr.resize(n);
        iota(all(pr), 0);
        sz.assign(n, 1);
    }
    int get(int v) {
        if (pr[v] == v) return v;
        return pr[v] = get(pr[v]);
    }
    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        pr[b] = a;
        return true;
    }
};
