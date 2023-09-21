#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// floating point errors
// #pragma GCC optimize("Ofast,unroll-loops")

// safe
// #pragma GCC optimize("O3,unroll-loops")

// doesn't work in yandex
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// doesn't work in some judges
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt,tune=native")

// safe
// #pragma GCC target("sse4.2,bmi,bmi2,lzcnt,popcnt")

template <typename T1, typename T2>
inline void mine(T1 &x, const T2 &y) {
    if (y < x)
        x = y;
}
template <typename T1, typename T2>
inline void maxe(T1 &x, const T2 &y) {
    if (x < y)
        x = y;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &b) {
    os << b.first << ' ' << b.second;
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &b) {
    for (const auto &k : b)
        os << k << ' ';
    return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &b) {
    for (auto &k : b)
        is >> k;
    return is;
}

template <typename T>
ostream &operator<<(ostream &os, const set<T> &b) {
    for (const auto &k : b)
        os << k << ' ';
    return os;
}

void dbg_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << "   " << H;
    dbg_out(T...);
}

#ifdef LOCAL_SERGEY
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define pb push_back
#define eb emplace_back
#define ppb pop_back()
#define mp make_pair
#define fx(x, a) for (auto &x : a)
#define siz(x) (long long)x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define left leftkekmda
#define right rightkekmda

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using str = string;

template <typename T>
using V = vector<T>;

using vi = V<int>;
using vl = V<ll>;
using vch = V<char>;
using vpii = V<pii>;
using vvpii = V<V<pii>>;
using vpll = V<pll>;
using vvpll = V<V<pll>>;
using vvi = V<vi>;
using vvl = V<vl>;
using vvch = V<vch>;

const ld PI = 4 * atan(1);
const ld EPS = 1e-8;

int sgn(ld x) {
    if (x > EPS)
        return 1;
    if (x < -EPS)
        return -1;
    return 0;
}

ld fix_angle(ld x) {
    if (x > 0)
        x = min(x, 1 - EPS);
    if (x < 0)
        x = max(x, -1 + EPS);
    return x;
}

ld mysqrt(ld x) {
    if (x < 0)
        return 0;
    return sqrt(x);
}

ld sqr(ld x) {
    return x * x;
}

bool eq(ld a, ld b) {
    return abs(a - b) <= EPS;
}

bool lt(ld a, ld b) {
    return a + EPS < b;
}

bool gt(ld a, ld b) {
    return a - EPS > b;
}

bool leq(ld a, ld b) {
    return a - EPS <= b;
}

bool geq(ld a, ld b) {
    return a + EPS >= b;
}

struct pt {
    ld x = 0;
    ld y = 0;
    pt() = default;
    explicit pt(ld x, ld y) : x(x), y(y) {
    }
    explicit pt(pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    pt perp() {
        return pt(-y, x);
    }

    pt norm() const {
        ld d = len();
        assert(sgn(d) == 1);
        return pt(x / d, y / d);
    }

    pt turn(ld a) const {
        return pt(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    ld len2() const {
        return x * x + y * y;
    }

    ld len() const {
        return sqrt(x * x + y * y);
    }

    pt operator+(pt p) const {
        return pt(x + p.x, y + p.y);
    }

    pt operator-(pt p) const {
        return pt(x - p.x, y - p.y);
    }

    pt operator*(ld d) const {
        return pt(x * d, y * d);
    }
    ld operator*(pt p) const {
        return x * p.y - y * p.x;
    }

    ld operator^(pt p) const {
        return x * p.x + y * p.y;
    }

    bool operator==(const pt &rhs) const {
        return eq(x, rhs.x) && eq(y, rhs.y);
    }

    bool operator<(const pt &p) const {
        return lt(x, p.x) || (eq(x, p.x) && lt(y, p.y));
    }
};

istream &operator>>(istream &in, pt &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, const pt &p) {
    out << p.x << ' ' << p.y;
    return out;
}

#define vec pt

ld dist2(pt a, pt b) {
    return pt(a, b).len2();
}

ld dist(pt a, pt b) {
    return pt(a, b).len();
}

ld ang(pt a, pt b) {
    return atan2(a * b, a ^ b);
}

struct line {
    ld a = 0;
    ld b = 0;
    ld c = 0;
    line() = default;
    line(ld a, ld b, ld c) : a(a), b(b), c(c) {
    }
    line(pt p1, pt p2) : a(p1.y - p2.y), b(p2.x - p1.x), c(-a * p1.x - b * p1.y) {
        make_normal();
    }
    ld get(pt p) const {
        return p.x * a + p.y * b + c;
    }
    void make_normal() {
        ld norm = sqrt(a * a + b * b);
        assert(sgn(norm) == 1);
        a /= norm;
        b /= norm;
        c /= norm;
    }
    ld dist(pt p) const {
        return abs(get(p)) / sqrt(sqr(a) + sqr(b));
    }
    pt project(pt p) const {
        vec norm(a, b);
        ld sd = get(p) / norm.len();
        return p + (norm * (-sd / norm.len()));
    }
    bool operator==(const line &other) const {
        return eq(a * other.b, b * other.a) && eq(a * other.c, c * other.a) && eq(b * other.c, c * other.b);
    }
};

bool are_parallel_lines(line f1, line f2) {
    return sgn(f1.a * f2.b - f1.b * f2.a) == 0;
}

pair<pt, int> cross_lines(line f1, line f2) {
    // 0 -- no intersection
    // 1 -- 1 point
    // 2 -- coincide
    ld d = f1.a * f2.b - f1.b * f2.a;
    if (sgn(d) == 0) {
        return {pt(), (f1 == f2 ? 2 : 0)};
    }
    ld x = f1.c * f2.b - f1.b * f2.c;
    ld y = f1.a * f2.c - f1.c * f2.a;
    return {pt(x / -d, y / -d), 1};
}

ld dist_to_seg(pt a, pt b, pt c) {
    ld res = min(dist(a, c), dist(b, c));
    vec ab(a, b);
    vec ac(a, c);
    vec ba(b, a);
    vec bc(b, c);
    if ((ab ^ ac) > 0 && (ba ^ bc) > 0)
        return abs(ac * bc) / dist(a, b);
    return res;
}

bool is_on_seg(pt a, pt b, pt c) {
    if (a == b) {
        return a == c;
    }
    vec ab(a, b);
    vec ac(a, c);
    vec ba(b, a);
    vec bc(b, c);
    return sgn(ab * ac) == 0 && sgn(ab ^ ac) >= 0 && sgn(ba ^ bc) >= 0;
}

bool are_crossed(ld l1, ld r1, ld l2, ld r2) {
    // at least one common point
    if (l1 > r1)
        swap(l1, r1);
    if (l2 > r2)
        swap(l2, r2);
    return geq(min(r1, r2), max(l1, l2));
}

bool are_crossed(pt a, pt b, pt c, pt d) {
    // at least one common point
    if (!are_crossed(a.x, b.x, c.x, d.x))
        return false;
    if (!are_crossed(a.y, b.y, c.y, d.y))
        return false;
    vec ab(a, b);
    vec ac(a, c);
    vec ad(a, d);
    if (sgn(ab * ac) * sgn(ab * ad) == 1)
        return false;
    vec cd(c, d);
    vec ca(c, a);
    vec cb(c, b);
    if (sgn(cd * ca) * sgn(cd * cb) == 1)
        return false;
    return true;
}

pair<pt, bool> intersect_segments(pt a, pt b, pt c, pt d) {
    if (a == b) {
        if (is_on_seg(c, d, a)) {
            return {a, true};
        } else {
            return {pt(), 0};
        }
    }
    if (c == d) {
        return intersect_segments(c, d, a, b);
    }

    vec ab(a, b);
    vec ac(a, c);
    vec ad(a, d);
    if (eq(ab * ac, 0) && eq(ab * ad, 0)) {
        for (int i = 0; i < 2; ++i) {
            if (is_on_seg(a, b, c))
                return {c, true};
            if (is_on_seg(a, b, d))
                return {d, true};
            swap(a, c);
            swap(b, d);
        }
        return {pt(), false};
    }
    auto res = cross_lines(line(a, b), line(c, d));
    assert(res.second != 2);
    if (res.second == 0) {
        return res;
    }
    if (is_on_seg(a, b, res.first) && is_on_seg(c, d, res.first)) {
        return res;
    }
    return {pt(), 0};
}

vector<pt> build_hull(vector<pt> pts) {
    int n = pts.size();
    pt p = pts[0];
    for (int i = 0; i < n; ++i) {
        mine(p, pts[i]);
    }
    for (int i = 0; i < n; ++i) {
        pts[i] = pt(p, pts[i]);
    }
    sort(all(pts), [&](pt a, pt b) {
        if (eq(a * b, 0)) {
            return a.len2() < b.len2();
        }
        return a * b > 0;
    });
    vector<pt> hull = {pts[0]};
    for (int i = 1; i < n; ++i) {
        while (hull.size() > 1) {
            if (leq(vec(hull[siz(hull) - 2], hull.back()) * vec(hull.back(), pts[i]), 0)) {
                hull.ppb;
            } else {
                break;
            }
        }
        hull.pb(pts[i]);
    }
    for (auto &x : hull) {
        x = x + p;
    }
    return hull;
}


ld perimeter(const vector<pt> &p) {
    int n = p.size();
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += pt(p[i], p[i + 1 < n ? i + 1 : 0]).len();
    }
    return ans;
}

ld area(const vector<pt> &p) {
    int n = p.size();
    ld res = 0;
    for (int i = 0; i < n; ++i) {
        res += p[i] * p[(i + 1 < n ? i + 1 : 0)];
    }
    return abs(res) / 2;
}

bool is_convex(const vector<pt> &p) {
    // allows 3 points on one line
    int n = p.size();
    int was = 0;
    for (int i = 0; i < n; ++i) {
        int pr = (i == 0 ? n - 1 : i - 1);
        int nx = (i + 1 == n ? 0 : i + 1);
        int cur = sgn(vec(p[pr], p[i]) * vec(p[i], p[nx]));
        if (was && cur && was != cur) {
            return false;
        }
        if (cur)
            was = cur;
    }
    return true;
}

bool is_in_poly_fast(vector<pt> &p, pt a, bool allow_bound) {
    // adjust this constant
    static const int ADDP = 1e9;
    int n = p.size();
    bool sum = false;
    pt b = a + pt(ADDP, 1);
    for (int i = 0; i < n; ++i) {
        pt l = p[i];
        pt r = p[i + 1 == n ? 0 : i + 1];
        if (is_on_seg(l, r, a)) {
            return allow_bound;
        }
        sum ^= are_crossed(a, b, l, r);
    }
    return sum;
}

bool is_in_poly_slow(vector<pt> &p, pt a, bool allow_bound) {
    int n = p.size();
    ld sum = 0;
    for (int i = 0; i < n; ++i) {
        pt l = p[i];
        pt r = p[i + 1 == n ? 0 : i + 1];
        if (is_on_seg(l, r, a)) {
            return allow_bound;
        }
        sum += ang(vec(a, l), vec(a, r));
    }
    return abs(sum) > PI / 2;
}

bool is_in_angle(pt a, pt o, pt b, pt p) {
    // works for non degenerate angle
    if (vec(o, a) * vec(o, b) < 0) {
        swap(a, b);
    }
    vec oa(o, a);
    vec op(o, p);
    vec ob(o, b);
    return sgn(oa * op) >= 0 && sgn(op * ob) >= 0;
}

bool is_in_triangle(pt a, pt b, pt c, pt p) {
    // works for non degenerate triangle
    return is_in_angle(c, a, b, p) && is_in_angle(a, b, c, p);
}

bool is_in_convex_poly(vector<pt> &p, pt a) {
    // works for non degenerate convex polygon in counterclockwise order
    int n = p.size();
    if (lt(vec(p[0], p[1]) * vec(p[0], a), 0))
        return false;
    if (gt(vec(p[0], p[n - 1]) * vec(p[0], a), 0))
        return false;
    int L = 1;
    int R = n - 1;
    while (R - L > 1) {
        int mid = (L + R) / 2;
        if (is_in_angle(p[1], p[0], p[mid], a)) {
            R = mid;
        } else {
            L = mid;
        }
    }
    return is_in_triangle(p[0], p[L], p[R], a);
}

pair<int, int> tangents_alex(vector<pt> &p, pt &a) {
    // thx to alex nekrasov
    int n = p.size();
    int l = 0;
    while ((1ll << (l + 1)) <= n)
        ++l;
    auto findWithSign = [&](int val) {
        int i = 0;
        for (int k = l; k >= 0; --k) {
            int i1 = (i - (1 << k) + n) % n;
            int i2 = (i + (1 << k)) % n;
            if (sgn(vec(a, p[i1]) * vec(a, p[i])) == val)
                i = i1;
            if (sgn(vec(a, p[i2]) * vec(a, p[i])) == val)
                i = i2;
        }
        return i;
    };
    return {findWithSign(1), findWithSign(-1)};
}

struct cir {
    pt c;
    ld r;
    cir(pt c, ld r) : c(c), r(r) {
    }

    cir(pt a, pt b, pt c) {
        pt mab((a.x + b.x) / 2, (a.y + b.y) / 2);
        vec ab = pt(a, b).perp();
        line l1(mab, mab + ab);

        pt mac((a.x + c.x) / 2, (a.y + c.y) / 2);
        vec ac = pt(a, c).perp();
        line l2(mac, mac + ac);

        c = cross_lines(l1, l2).first;
        r = dist(c, a);
        assert(eq(r, dist(c, a)) && eq(r, dist(c, b)) && eq(r, dist(c, c)));
    }

    vector<pt> tang(pt p) {
        // returns vector of tangent points to the circle from a given point
        ld d = dist(p, c);
        if (eq(d, r)) {
            return {p};
        }
        if (leq(d, r)) {
            return {};
        }
        ld a = sqr(r) / d;
        vec v = vec(c, p).norm();
        pt mid = c + v * a;
        ld x = mysqrt(sqr(r) - sqr(a));
        v = v.perp();
        return {mid + v * x, mid + v * (-x)};
    }
};

vector<pt> cross_circles(cir w1, cir w2) {
    // returns all intersection points, but only 3 if circles coincide

    if (w1.r < w2.r) {
        swap(w1.c, w2.c);
        swap(w1.r, w2.r);
    }
    if (eq(w1.r, w2.r) && w1.c == w2.c) {
        return {w1.c + pt(w1.r, 0), w1.c + pt(-w1.r, 0), w1.c + pt(0, w1.r)};
    }
    ld len = dist(w1.c, w2.c);
    if (gt(len, w1.r + w2.r) || gt(w1.r, len + w2.r)) {
        return {};
    }
    ld d = (sqr(w1.r) - sqr(w2.r) + sqr(len)) / 2 / len;
    vec v(w1.c, w2.c);
    v = v.norm();
    pt a = w1.c + v * d;
    if (eq(len, w1.r + w2.r) || eq(w1.r, w2.r + len)) {
        return {a};
    }
    v = v.perp() * sqrt(sqr(w1.r) - sqr(d));
    return {a + v, a - v};
}

vector<pt> cross_circle_line(cir w, line l) {
    // returns all the intersection points
    ld len = l.dist(w.c);
    if (lt(w.r, len)) {
        return {};
    }
    pt p = l.project(w.c);
    if (leq(w.r, len)) {
        return {p};
    }
    ld x = mysqrt(sqr(w.r) - sqr(len));
    vec dv = vec(-l.b, l.a).norm();
    return {p + dv * x, p + dv * (-x)};
}

vector<line> common_tangents(cir w1, cir w2) {
    // thx to igor markelov
    vector<line> res;
    auto calc = [&](pt c, ld r1, ld r2) {
        ld r = r2 - r1;
        ld z = sqr(c.x) + sqr(c.y);
        ld d = z - sqr(r);
        if (sgn(d) == -1)
            return;
        d = sqrt(abs(d));
        line l;
        l.a = (c.x * r + c.y * d) / z;
        l.b = (c.y * r - c.x * d) / z;
        l.c = r1;
        res.push_back(l);
    };
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            calc(pt(w2.c, w1.c), w1.r * i, w2.r * j);
        }
    }
    for (auto &l : res) {
        l.c -= l.a * w1.c.x + l.b * w1.c.y;
    }
    return res;
}

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
