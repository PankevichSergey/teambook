struct nd {
	int key;
	int prior;
	int sz;
	nd *l;
	nd *r;
	nd (int x): key(x), prior(rng()), sz(1), l(nullptr), r(nullptr) {}
};

void print(nd * t, bool end = true) {
	if (!t)
		return;
	print(t->l, false);
	cout << t->key << ' ' << t->sz << "  "; 
	print(t->r, false);
	if (end) cout << endl;
}

int getsz(nd * t) {
	if (!t)
		return 0;
	return t->sz;
}

void upd(nd * t) {
	t->sz = 1 + getsz(t->l) + getsz(t->r);
}

void push(nd * t) {

}

pair<nd*, nd*> splitx(nd * t, int x) {
	if (!t)
		return {nullptr, nullptr};
	push(t);
	if (t->key > x) {
		auto spl = splitx(t->l, x);
		t->l = spl.second;
		upd(t);
		return {spl.first, t};
	} else {
		auto spl = splitx(t->r, x);
		t->r = spl.first;
		upd(t);
		return {t, spl.second};
	}
}

pair<nd*, nd*> splitk(nd * t, int k) {
	if (!t)
		return {nullptr, nullptr};
	push(t);
	if (getsz(t->l) >= k) {
		auto spl = splitk(t->l, k);
		t->l = spl.second;
		upd(t);
		return {spl.first, t};
	} else {
		auto spl = splitk(t->r, k - getsz(t->l) - 1);
		t->r = spl.first;
		upd(t);
		return {t, spl.second};
	}
}

nd * merge(nd * t1, nd * t2) {
	if (!t1)
		return t2;
	if (!t2)
		return t1;
	if (t1->prior > t2->prior) {
		push(t1);
		t1->r = merge(t1->r, t2);
		upd(t1);
		return t1;
	} else {
		push(t2);
		t2->l = merge(t1, t2->l);
		upd(t2);
		return t2;
	}
}

int max(nd * t) {
	push(t);
	if (t->r)
		return max(t->r);
	return t->key;
}

int min(nd * t) {
	push(t);
	if (t->l)
		return min(t->l);
	return t->key;
}

nd * insert(nd * t, int x) {
	nd * key = new nd(x);
	auto spl = splitx(t, x);
	auto spl2 = splitx(spl.first, x - 1);
	return merge(merge(spl2.first, key), spl.second);
}

nd * erasex(nd * t, int x) {
	auto spl = splitx(t, x);
	auto spl2 = splitx(spl.first, x - 1);
	return merge(spl2.first, spl.second);
}

nd * erasek(nd * t, int k) {
	auto spl = splitk(t, k);
	auto spl2 = splitk(spl.first, k - 1);
	return merge(spl2.first, spl.second);
}

int getk(nd * &t, int k) {
	auto spl = splitk(t, k);
	auto spl2 = splitk(spl.first, k - 1);
	int res = spl2.second->key;
	t = merge(merge(spl2.first, spl2.second), spl.second);
	return res;
}

int lessx(nd * &t, int x) {
	auto spl = splitx(t, x - 1);
	int res = getsz(spl.first);
	t = merge(spl.first, spl.second);
	return res;
}

int first_more(nd *&t, int x) {
	auto spl = splitx(t, x);
	int res;
	if (!spl.second)
		res = INF;
	else
		res = min(spl.second);
	t = merge(spl.first, spl.second);
	return res;
}

int lower_bound(nd *&t, int x) {
	auto spl = splitx(t, x - 1);
	int res;
	if (!spl.second)
		res = INF;
	else
		res = min(spl.second);
	t = merge(spl.first, spl.second);
	return res;
}

int first_less(nd *&t, int x) {
	auto spl = splitx(t, x - 1);
	int res;
	if (!spl.first)
		res = INF;
	else
		res = max(spl.first);
	t = merge(spl.first, spl.second);
	return res;
}
