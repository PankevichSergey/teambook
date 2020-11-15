int t[4 * MX];
int add[4 * MX];
 
 
void push(int v, int l, int r) {
	if (l + 1 == r || add[v] == -INF)
		return;
	add[2 * v] = add[v];
	add[2 * v + 1] = add[v];
	t[2 * v] = add[v];
	t[2 * v + 1] = add[v];
	add[v] = -INF;
	return;
}
 
void upd(int v, int l, int r, int x, int cl, int cr) {
	push(v, cl, cr);
	if (cl >= r || cr <= l)
		return;
	if (cl >= l && cr <= r) {
		t[v] = add[v] = x;
		return;
	}
	int m = (cl + cr) / 2;
	upd(2 * v, l, r, x, cl, m);
	upd(2 * v + 1, l, r, x, m, cr);
	t[v] = min(t[2 * v], t[2 * v + 1]);
}
 
int get(int v, int l, int r, int cl, int cr) {
	push(v, cl, cr);
	if (cl >= r || cr <= l)
		return INF;
	if (cl >= l && cr <= r)
		return t[v];
	int m = (cl + cr) / 2;
	return min(get(2 * v, l, r, cl, m), get(2 * v + 1, l, r, m, cr));
}
