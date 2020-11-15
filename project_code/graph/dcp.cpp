#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>
#include <utility>
#include <set>
#include <stack>
#include <deque>
#include <ctime>
#include <random>
#include <cassert>
#include <cmath>
#include <climits>
#include <queue>
#include <cstring>
#include <bitset>
#include <iomanip>
#include <chrono>

/*
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("popcnt")
#pragma GCC target("avx2")
*/


#ifdef LOCAL
    #define dbg(x) cout << #x << " : " << x << endl;
#else
    #define dbg(x)
#endif

#define pb push_back
#define ppb pop_back()
#define mp make_pair
#define fi(a, b) for (int i = a; i < b; i++)
#define fj(a, b) for (int j = a; j < b; j++)
#define fk(a, b) for (int k = a; k < b; k++)
#define fi1(a, b) for (int i = a - 1; i >= b; i--)
#define fj1(a, b) for (int j = a - 1; j >= b; j--)
#define fk1(a, b) for (int k = a - 1; k >= b; k--)
#define fx(x, a) for (auto& x : a)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define rep1(i, a, b) for (int i = a - 1; i >= b; --i)
#define siz(x) (int)x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

using namespace std;

template<typename T1, typename T2>inline void mine(T1 &x, T2 y) { if (x > y) x = y; }
template<typename T1, typename T2>inline void maxe(T1 &x, T2 y) { if (x < y) x = y; }

ostream& operator << (ostream &a, const vector<int> &b) {
    for (auto k : b) cout << k << ' ';
    return a;
}


typedef long long ll;
typedef unsigned long long ull;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;
typedef map<int, int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<ch> vch;
typedef vector<vch> vvch;
typedef vector<str> vs;



const int MOD = 1000000007;
const int INF = 1000000050;
const long long BIG = (long long)2e18 + 50;
const int MX = 300010;
const double EPS = 1e-9;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vpii t[4 * MX];

void upd(int v, int l, int r, pii e, int cl, int cr) {
    if (cl >= r || cr <= l)
        return;
    if (cl >= l && cr <= r) {
        t[v].pb(e);
        return;
    }
    int m = (cl + cr) / 2;
    upd(2 * v, l, r, e, cl, m);
    upd(2 * v + 1, l, r, e, m, cr);
} 


int ans[MX];
vi reqs[MX];

int p[MX];
int sz[MX];
int cnt;
int get(int v) {
    if (p[v] == v)
        return v;
    return get(p[v]);
}

vector<pair<pii, int>> pers;
void unite(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) {
        pers.pb({{a, b}, 0});
        return;
    }
    if (sz[a] < sz[b])
        swap(a, b);
    pers.pb({{a, b}, 1});
    --cnt;
    p[b] = a;
    sz[a] += sz[b];
}

void rollback() {
    if (pers.back().second) {
        int a = pers.back().first.first;
        int b = pers.back().first.second;
        ++cnt;
        p[b] = b;
        sz[a] -= sz[b];
    }
    pers.ppb;
}

void dfs(int v, int cl, int cr) {
    for (pii e : t[v])
        unite(e.first, e.second);

    if (cl + 1 == cr) {
        for (int id: reqs[cl]) {
            ans[id] = cnt;
        }
    } else {
        dfs(2 * v, cl, (cl + cr) / 2);
        dfs(2 * v + 1, (cl + cr) / 2, cr);
    }

    for (int i = 0; i < t[v].size(); ++i)
        rollback();
}


map<pii, vi> l;
map<pii, vi> r;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    if (m == 0)
        return 0;
    cnt = n;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    int q = 0;
    for (int i = 0; i < m; ++i) {
        char c;
        cin >> c;
        if (c == '?') {
            reqs[i].pb(q++);
        } else {
            int a, b;
            cin >> a >> b;
            --a, --b;
            if (a > b)
                swap(a, b);
            pii e = {a, b};
            if (c == '+')
                l[e].pb(i);
            else
                r[e].pb(i);
        }
    }
    for (auto kek : l) {
        pii e = kek.first;
        if (r[e].size() != kek.second.size())
            r[e].pb(m);
        vi lin = kek.second;
        vi rin = r[e];
        assert(rin.size() == lin.size());
        for (int i = 0; i < lin.size(); ++i) {
            upd(1, lin[i], rin[i], e, 0, m);
        }
    }
    dfs(1, 0, m);
    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}
