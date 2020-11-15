struct nd {
	int l;
	int r;
	int sum;
	nd (int _l = 0, int _r = 0, int _sum = 0) {
		l = _l;
		r = _r;
		sum = _sum;
	}
};

nd t[MX * 20];
int rt[MX];

int sz = 0;
int init() {
  t[sz] = nd();
  return sz++;
}


void build(int v, int l, int r) {
	if (l + 1 == r)
		return;
	int m = (l + r) / 2;
	build(t[v].l = init(), l, m);
	build(t[v].r = init(), m, r);
}


int get(int v1, int v2, int k, int cl, int cr) {
	if (cl + 1 == cr)
		return cl;
	int m = (cl + cr) / 2;
	int sumleft = t[t[v2].l].sum - t[t[v1].l].sum;
	if (sumleft >= k)
		return get(t[v1].l, t[v2].l, k, cl, m);
	return get(t[v1].r, t[v2].r, k - sumleft, m, cr);
}

int upd(int v, int i, int cl, int cr) {
	int u = init();
	if (cl + 1 == cr) {
		t[u].sum = t[v].sum + 1;
		return u;
	}
	t[u] = t[v];
	int m = (cl + cr) / 2;
	if (i < m) {
		t[u].l = upd(t[v].l, i, cl, m);
	} else {
		t[u].r = upd(t[v].r, i, m, cr);
	}
	t[u].sum = t[t[u].l].sum + t[t[u].r].sum;
	return u;
}
