struct node {
	int pr;
	int s;
	int to[K];
	node () {
		pr = -1;
		s = -1;
		memset(to, -1, sizeof(to));
	}
};

vector<node> t;

int add(int a, char ch) {
	int b = t.size();
	t.push_back(node());
	t[b].pr = a;
	t[b].s = 0;
	while (a != -1) {
		if (t[a].to[ch] == -1) {
			t[a].to[ch] = b;
			a = t[a].s;
			continue;
		}
		int c = t[a].to[ch];
		if (t[c].pr == a) {
			t[b].s = c;
			break;
		}
		int d = t.size();
		t.push_back(node());
		t[d].pr = a;
		t[d].s = t[c].s;
		t[b].s = t[c].s = d;
		memcpy(t[d].to, t[c].to, sizeof(t[d].to));
		for (; a != -1 && t[a].to[ch] == c; a = t[a].s)
			t[a].to[ch] = d;
		break;
	}
	return b;
}

int last;

void init() {
	last = 0;
	t.push_back(node());
}

void addstring(str & s) {
	fx(x, s)
		last = add(last, x);
}

bool findstring(str & s) {
	int cur = 0;
	fx(x, s) {
		cur = t[cur].to[x];
		if (cur == -1)
			return false;
	}
   	return true;
}
