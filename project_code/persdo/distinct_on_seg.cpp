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
const int MX = 1000100;
const double EPS = 1e-9;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct nd {
	int l;
	int r;
	int sum;
	nd (int _l = 0, int _r = 0, int _sum = 0) {
		l = _l;
		r = _r;
		sum = _sum;
	}
};

nd t[40 * MX];
int rt[MX];
int sz = 0;

int init() {
	t[sz] = nd();
	return sz++;
}

int a[MX];
int pr[MX];

int upd(int v, int i, int x, int cl, int cr) {
	int u = init();
	t[u] = t[v];
	if (cl + 1 == cr) {
		t[u].sum += x;
		return u;
	}
	int m = (cl + cr) / 2;
	if (i < m)
		t[u].l = upd(t[u].l, i, x, cl, m);
	else
		t[u].r = upd(t[u].r, i, x, m, cr);
	t[u].sum = t[t[u].l].sum + t[t[u].r].sum;
	return u;
}

int get(int v, int l, int r, int cl, int cr) {
	if (cl >= r || cr <= l)
		return 0;
	if (cl >= l && cr <= r)
		return t[v].sum;
	int m = (cl + cr) / 2;
	return get(t[v].l, l, r, cl, m) + get(t[v].r, l, r, m, cr);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n;
    
    rt[0] = init();
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
    	rt[i] = upd(rt[i - 1], i - 1, 1, 0, n);
    	if (pr[a[i]])
    		rt[i] = upd(rt[i], pr[a[i]] - 1, -1, 0, n);
    	pr[a[i]] = i;
    }
    cin >> q;
    while (q--) {
    	int l, r;
    	cin >> l >> r;
    	cout << get(rt[r], l - 1, n, 0, n) << '\n';
    }
}
