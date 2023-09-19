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
#include <unordered_set>

using namespace std;

// floating point errors
//#pragma GCC optimize("Ofast,unroll-loops")



// safe
// #pragma GCC optimize("O3,unroll-loops")

// doesn't work in yandex
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
using ld = float;
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

    ld len2() const {
        return x * x + y * y;
    }

    ld operator*(pt p) const {
        return x * p.y - y * p.x;
    }

    ld operator^(pt p) const {
        return x * p.x + y * p.y;
    }

    bool operator==(const pt &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator<(const pt &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

istream &operator>>(istream &in, pt &p) {
    ll x, y;
    in >> x >> y;
    p.x = x;
    p.y = y;
    return in;
}

ostream &operator<<(ostream &out, pt &p) {
    out << p.x << ' ' << p.y;
    return out;
}

#define vec pt


const int N = 20100;

vector<pt>& build_hull(const set<pt>& pts) {
    pt f = *pts.begin();
    static vector<pt> hull;
    hull = {f};
    while (true) {
        pt kek = pt(1e5, 1e5);
        pt best = kek;
        for (auto p : pts) {
            if (p == hull.back()) continue;
            if (best == kek) {
                best = p;
            } else {
                vec v1(hull.back(), best);
                vec v2(hull.back(), p);
                if (v2 * v1 > 0 || (v2 * v1 == 0 && v2.len2() < v1.len2())) {
                    best = p;
                }
            }
        }
         if (best == kek || best == f) {
            return hull;
        }
        hull.push_back(best);
    }
}


void solve() {
    int n;
    cin >> n;
    vector<pt> pts(n);
    cin >> pts;
    vector<int> ans(n);
    int t = 1;

    map<pt, int> id;
    set<pt> rest;
    for (int i = 0; i < n; ++i) {
        rest.insert(pts[i]);
        id[pts[i]] = i;
    }
    while (rest.size()) {
        auto res = build_hull(rest);
        for (pt p : res) {
            ans[id[p]] = t;
            rest.erase(p);
        }
        ++t;
    }
    for (int x : ans) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
