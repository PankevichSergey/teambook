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



#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")



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

int MOD;

ll add(ll a, ll b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

ll sub(ll a, ll b) {
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

ll mult(ll a, ll b) {
    return a * b % MOD;
}

ll powmod(ll a, ll p) {
    if (p == 0) return 1;
    if (p & 1) return mult(a, powmod(a, p - 1));
    return powmod(mult(a, a), p / 2);
}

ll rev(ll a) {
    return powmod(a, MOD - 2);
}

const int C = 33000;
int g[C];
int rg[C];
bool bad[C];
vi fact[C];
int B[C];
unordered_map<int, int> have[C];

void calc() {
    for (MOD = 2; MOD < C; ++MOD) {
        if (bad[MOD]) continue;
        for (g[MOD] = 2;;++g[MOD]) {
            bool ok = true;
            int pw = MOD - 1;
            fx(p, fact[MOD - 1]) {
                ok &= powmod(g[MOD], pw / p) != 1;
            }
            if (ok) break;
        }
        rg[MOD] = rev(g[MOD]);
        B[MOD] = min(100, MOD - 1);
        int pw = 1;
        int gb = powmod(g[MOD], B[MOD]);
        for (int i = 0; i * B[MOD] < MOD - 1; ++i) {
            have[MOD][pw] = i;
            pw = mult(pw, gb);
        }
        for (int j = MOD; j < C; j += MOD) {
            bad[j] = 1;
            fact[j].pb(MOD);
        }
    }
}

int dlog(int x) {
    for (int r = 0; r < B[MOD]; ++r) {
        auto it = have[MOD].find(x);
        if (it != have[MOD].end())
            return it->second * B[MOD] + r;
        x = mult(x, rg[MOD]);
    }
    throw;
}

void no() {
    cout << "No root\n";
}


void solve() {
    int a;
    cin >> a >> MOD;
    a %= MOD;
    if (MOD == 1) {
        no();
        return;
    }
    if (MOD == 2) {
        cout << "1\n";
        return;
    }
    int la = dlog(a);
    if (la % 2 == 1) {
        no();
        return;
    }
    int left = powmod(g[MOD], la / 2);
    int right = mult(left, powmod(g[MOD], (MOD - 1) / 2));
    if (left > right) swap(left, right);
    cout << left << ' ' << right << '\n';
}



int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    calc();

    int q;
    cin >> q;
    while (q--) solve();
}
