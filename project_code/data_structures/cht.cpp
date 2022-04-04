ll div_up(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b);
}

struct line {
    ll k;
    ll b;
    ll get(ll x) {
        return k * x + b;
    }
    ll sec(const line& rhs) const {
        ll db = rhs.b - b;
        ll dk = k - rhs.k;
        if (dk < 0) {
            dk *= -1;
            db *= -1;
        }
        assert(dk != 0);
        return div_up(db, dk);
    }
};

// const int N = 2e5 + 10;
int sz = 0;
line hull[N];
void add(line l) {
    while (sz >= 2 && hull[sz - 1].sec(hull[sz - 2]) >= l.sec(hull[sz - 1])) {
        --sz;
    }
    hull[sz++] = l;
}
ll get(int x) {
    int L = 0;
    int R = sz - 1;
    while (R - L > 1) {
        int m = (L + R) / 2;
        if (hull[m + 1].get(x) >= hull[m].get(x)) {
            L = m + 1;
        } else {
            R = m;
        }
    }
    ll res = hull[L].get(x);
    if (L + 1 < sz) maxe(res, hull[L + 1].get(x));
    return res;
}
