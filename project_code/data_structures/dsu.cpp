int p[MX];
int sz[MX];

int get(int v) {
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void unite(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
}
