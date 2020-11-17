struct inf {
    int l;
    int r;
    int cnt;
    int sum;
    inf (int _l = 0, int _r = 0, int _cnt = 0, int _sum = 0) {
        l = _l;
        r = _r;
        cnt = _cnt;
        sum = _sum;
    }
};


inf t[60 * MX];
int sz = 0;
int init() {
    assert(sz < 60 * MX);
    return sz++;
}

int makel(int v) {
    if (!t[v].l) t[v].l = init();
    return t[v].l;
}

int maker(int v) {
    if (!t[v].r) t[v].r = init();
    return t[v].r;
}

void upd(int v, int x, int y, int cl, int cr) {
    if (cl + 1 == cr) {
        t[v].cnt += y;
        t[v].sum += y * x;
        return;
    }
    int m = (cl + cr) / 2;
    if (x < m) {
        upd(makel(v), x, y, cl, m);
    } else {
        upd(maker(v), x, y, m, cr);
    }
    t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
    t[v].cnt = t[t[v].l].cnt + t[t[v].r].cnt;
}

int firstk(int v, int k) {
    if (t[v].cnt == k)
        return t[v].sum;
    if (!t[v].l && !t[v].r)
        return t[v].sum / t[v].cnt * k;
    if (t[t[v].l].cnt >= k)
        return firstk(t[v].l, k);
    return t[t[v].l].sum + firstk(t[v].r, k - t[t[v].l].cnt);
}

int lastk(int v, int k) {
    if (t[v].cnt == k)
        return t[v].sum;
    if (!t[v].l && !t[v].r)
        return t[v].sum / t[v].cnt * k;
    if (t[t[v].r].cnt >= k)
        return lastk(t[v].r, k);
    return t[t[v].r].sum + lastk(t[v].l, k - t[t[v].r].cnt);
}
