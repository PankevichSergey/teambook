#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <utility>
#include <algorithm>
#include <random>
#include <cmath>
#include <cassert>
#include <climits>
#include <ctime>
#include <chrono>


/*
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
*/


#ifdef LOCAL
    #define dbg(x) cout << #x << " : " << x << endl;
#else
    #define dbg(x)
#endif

#define int long long
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
#define left leftkekmda
#define right rightkekmda

using namespace std;

template<typename T1, typename T2>inline void mine(T1 &x, const T2 &y) { if (y < x) x = y; }
template<typename T1, typename T2>inline void maxe(T1 &x, const T2 &y) { if (x < y) x = y; }

template<typename T> ostream& operator << (ostream &os, const vector<T> &b) {
    for (auto &k : b) os << k << ' ';
    return os;
}
template<typename T> istream& operator >> (istream &is, vector<T> &b) {
    for (auto &k : b) is >> k;
    return is;
}


typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<ch> vch;
typedef vector<vch> vvch;
typedef vector<str> vs;





mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


struct edge {
    int v;
    int to;
    int c;
    int f;
    int cost;
    edge(int _v, int _to, int _c, int _f, int _cost): v(_v), to(_to), c(_c), f(_f), cost(_cost) {}
};

const int N = 51;
const int INF = 1e9 + 228;

vi g[N];
vector<edge> e;

void add(int a, int b, int c, int cost) {
    g[a].pb(e.size());
    e.pb(edge(a, b, c, 0, cost));
    g[b].pb(e.size());
    e.pb(edge(b, a, 0, 0, -cost));
}

int sum = 0;

void flow(int id, int cnt) {
    sum += e[id].cost * cnt;
    e[id].f += cnt;
    e[id ^ 1].f -= cnt;
}

int n;

int dist[N];
int pr[N];
int cnt[N];
int in[N];

int spfa() {
    for (int i = 1; i < n; ++i) {
        dist[i] = INF;
        in[i] = 0;
    }
    queue<int> q;
    q.push(0);
    in[0] = 1;
    while (q.size()) {
        int v = q.front();
        q.pop();
        in[v] = 0;
        fx(id, g[v]) {
            if (e[id].f < e[id].c) {
                int to = e[id].to;
                int cost = e[id].cost;
                if (dist[to] > dist[v] + cost) {
                    dist[to] = dist[v] + cost;
                    cnt[to] = cnt[v] + 1;
                    pr[to] = id;
                    if (cnt[to] >= n) {
                        vch used(n, 0);
                        int cur = to;
                        vi ids;
                        while (!used[cur]) {
                            used[cur] = 1;
                            ids.pb(pr[cur]);
                            cur = e[pr[cur]].v;    
                        }
                        ids.pb(pr[cur]);
                        int mnd = INF;
                        for (int i = siz(ids) - 1;;--i) {
                            if (ids[i] == ids.back()) break;
                            mine(mnd, e[ids[i]].c - e[ids[i]].f);
                        }
                        for (int i = siz(ids) - 1;;--i) {
                            if (ids[i] == ids.back()) break;
                            flow(ids[i], mnd);
                        }
                        return 0;
                    }
                    if (!in[to]) {
                        in[to] = 1;
                        q.push(to);
                    }   
                }
            }
        }
    }
    if (dist[n - 1] == INF) return -1;
    int cur = n - 1;
    while (cur != 0) {
        flow(pr[cur], 1);
        cur = e[pr[cur]].v;
    }
    return 1;
}

bool used[N];
int ford(int v, int mnp = INF) {
    if (used[v] || mnp == 0) return 0;
    used[v] = 1;
    if (v == n - 1) return mnp;
    fx(id, g[v]) {
        if (e[id].cost) continue;
        int can = ford(e[id].to, min(e[id].c - e[id].f, mnp));
        if (can > 0) {
            flow(id, can);
            return can;
        }
    }
    return 0;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            if (x == 0) continue;
            add(i, j, x, 0);
            add(i, j, INF, 1);
        }
    }
    int ans = 0, delta;
    while (delta = ford(0)) {
        memset(used, 0, sizeof(used));
        ans += delta;
    }
    while (sum <= k) {
        delta = spfa();
        if (delta == -1) {
            cout << ans << '\n';
            return 0;
        }
        ans += delta;
    }
    while (!spfa()) {
        if (sum <= k) {
            cout << ans << '\n';
            return 0;
        }
    }
    cout << ans - 1 << '\n';
}
