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
const ld EPS = 1e-9;

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
    if (x < 0) return 0;
    return sqrt(x);
}

ld sqr(ld x) {
    return x * x;
}

bool eq(ld a, ld b) {
    return abs(a - b) < EPS;
}

bool lt(ld a, ld b) {
    return a + EPS < b;
}

bool gt(ld a, ld b) {
    return a - EPS > b;
}

bool leq(ld a, ld b) {
    return a - EPS < b;
}

bool geq(ld a, ld b) {
    return a + EPS > b;
}

struct pt {
    ld x = 0;
    ld y = 0;
    pt() = default;
    explicit pt (ld x, ld y): x(x), y(y) {
    }
    explicit pt (pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    pt perp() {
        return pt(-y, x);
    }

    pt norm() {
        ld d = len();
        assert(sgn(d) == 1);
        return pt(x / d, y / d);
    }

    pt turn(ld a) {
        return pt(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    ld len2() {
        return x * x + y * y;
    }

    ld len() {
        return sqrt(x * x + y * y);
    }

    pt operator + (pt p) {
        return pt(x + p.x, y + p.y);
    }

    pt operator * (ld d) {
        return pt(x * d, y * d);
    }

    ld operator * (pt p) {
        return x * p.y - y * p.x;
    }

    ld operator ^ (pt p) {
        return x * p.x + y * p.y;
    }

    bool operator == (const pt& rhs) const {
        return eq(x, rhs.x) && eq(y, rhs.y);
    }

    bool operator < (const pt & p) const {
        return lt(x, p.x) || (eq(x, p.x) && lt(y, p.y));
    }
};

istream& operator >> (istream & cin, pt & p) {
    cin >> p.x >> p.y;
    return cin;
} 

ostream& operator << (ostream & cout, pt & p) {
    cout << p.x << ' ' << p.y;
    return cout;
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

ld segdist(pt a, pt b, pt c) {
    ld res = min(dist(a, c), dist(b, c));
    vec ab(a, b);
    vec ac(a, c);
    vec ba(b, a);
    vec bc(b, c);   
    if ((ab ^ ac) > 0 && (ba ^ bc) > 0) 
        return abs(ac * bc) / dist(a, b);
    return res;
}

vector<pt> build_hull(vector<pt> pts) {
    int n = pts.size();
    pt p = *min_element(all(pts));
    for (int i = 0; i < n; ++i) {
        pts[i] = pt(p, pts[i]);
    }
    sort(all(pts), [&](pt a, pt b){
        auto prod = a * b;
        if (eq(prod, 0)) {
            return a.len() < b.len();
        }
        return a * b > 0;
    });
    vector<pt> hull = {pts[0]};
    for (int i = 1; i < n; ++i) {
        while (hull.size() > 1) {
            if (leq(pt(hull[siz(hull) - 2], hull.back()) * pt(hull.back(), pts[i]), 0)) {
                hull.ppb;
            } else {
                break;
            }
        }
        hull.pb(pts[i]);
    }
    for (auto&x : hull) {
        x = x + p;
    }
    return hull;
}

struct line {
    ld a = 0;
    ld b = 0;
    ld c = 0;
    line() = default;
    line (ld a, ld b, ld c): a(a), b(b), c(c) {}
    line(pt p1, pt p2): a(p1.y - p2.y), b(p2.x - p1.x), c(-a * p1.x - b * p1.y) {}
    ld eval(pt p) const {
        return p.x * a + p.y * b + c;
    }
    void make_normal() {
        ld norm = sqrt(a * a + b * b);
        a /= norm;
        b /= norm;
        c /= norm;
    }
    ld dist(pt p) const {
        return abs(p.x * a + p.y * b + c) / sqrt(a * a + b * b);
    }
    bool operator == (const line& other) const {
        return eq(a * other.b, b * other.a) &&
               eq(a * other.c, c * other.a) &&
               eq(b * other.c, c * other.b);
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
        if (f1 == f2) {
            return {pt(), 2};
        } else {
            return {pt(), 0};
        }
    }
    ld x = f1.c * f2.b - f1.b * f2.c;
    ld y = f1.a * f2.c - f1.c * f2.a;
    return {pt(x / -d, y / -d), 1};
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
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return geq(min(r1, r2), max(l1, l2));
}


bool are_crossed(pt a, pt b, pt c, pt d) {
    // at least one common point
    if (!are_crossed(a.x, b.x, c.x, d.x)) return false;
    if (!are_crossed(a.y, b.y, c.y, d.y)) return false;
    vec ab(a, b);
    vec ac(a, c);
    vec ad(a, d);
    if (sgn(ab * ac) * sgn(ab * ad) == 1) return false;
    vec cd(c, d);
    vec ca(c, a);
    vec cb(c, b);
    if (sgn(cd * ca) * sgn(cd * cb) == 1) return false;
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
            if (is_on_seg(a, b, c)) return {c, 1};
            if (is_on_seg(a, b, d)) return {c, 1};
        }
        return {pt(), 0};
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


bool is_outside(vector<pt>& poly, pt p) {
    ld sum = 0;
    for (int i = 0; i < poly.size(); ++i) {
        int j = i + 1;
        if (j == poly.size()) {
            j = 0;
        }
        pt a = poly[i];
        pt b = poly[j];
        if (is_on_seg(poly[i], poly[j], p)) {
            return false;
        }
        sum += ang(vec(p, a), vec(p, b));
    }
    return sum < PI;
}

ld perimeter(vector<pt>& p) {
  ld ans = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i) {
    ans += vec(p[i], p[i + 1 < n ? i + 1 : 0]).len();
  }
  return ans;
}

struct cir {
    pt C;
    ld r;
    cir(pt C, ld r): C(C), r(r) {}

    cir(pt a, pt b, pt c) {
        pt mab((a.x + b.x) / 2, (a.y + b.y) / 2);
        vec ab = pt(a, b).perp();
        line l1(mab, mab + ab);

        pt mac((a.x + c.x) / 2, (a.y + c.y) / 2);
        vec ac = pt(a, c).perp();
        line l2(mac, mac + ac);

        C = cross_lines(l1, l2).first;
        r = dist(C, a);
        assert(eq(r, dist(C, a)) && eq(r, dist(C, b)) && eq(r, dist(C, c))); 
    }
    
    vector<pt> tang(pt p) {
        ld d = dist(p, C);
        if (eq(r, d))
            return {p};
        ld L = mysqrt(d * d - r * r);
        ld a = acos(fix_angle(L / d));
        vec pc(p, C);
        pc = pc * (L / d);
        return {p + pc.turn(a), p + pc.turn(-a)};
    }
};



// vector<pt> cross_circles(cir w1, cir w2) {
//     // returns all intersection points, but only 3 if circles coincide

//     if (w1.r < w2.r) {
//         swap(w1.c, w2.c);
//         swap(w1.r, w2.r);
//     }
//     if (eq(w1.r, w2.r) && w1.c == w2.c) {
//         return {w1.o + pt(w1.r, 0), w1.o + pt(-w1.r, 0), w1.o + pt(0, w1.r)};
//     }
//     ld len = (w1.c - w2.c).len();
//     if (gt(len, w1.r + w2.r)|| gt(w1.r, len + w2.r)) {
//         return {};
//     }
//     ld d = (sqr(w1.r) - sqr(w2.r) + sqr(len)) / 2 / len;
//     vec v = (w2.c - w1.c).norm();
//     pt a = w1.c + v * d;
//     if (sgn(len - w1.r - w2.r) == 0 || sgn(len + w2.r - w1.r) == 0) {
//         I1 = a;
//         return 1;
//     }
//     v = v.ort() * sqrt(sqr(w1.r) - sqr(d));
//     I1 = a + v;
//     I2 = a - v;
//     return 2;
// }

// vector<pt> cross_circles(cir w1, cir w2) {

// }


int main() {
    line a(1, 1, 1);
    line b(2, 2, 3);
    line c(1, 1, 0);
    line d(2, 0, 0);
    cout << (a == b) << '\n';
    cout << (c == d) << '\n';
}