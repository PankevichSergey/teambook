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
const int MX = 200010;
const int PW = 20;
const double EPS = 1e-9;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct nd {
	int l;
	int r;
	int sum;
	nd(int _l = 0, int _r = 0, int _sum = 0) {
		l = _l;
		r = _r;
		sum = _sum;
	}
};


nd t[PW * MX];
int sz = 0;
int init() {
	t[sz] = nd();
	return sz++;
}

int upd(int v, int i, int cl, int cr) {
	int u = init();
	t[u] = t[v];
	if (cl + 1 == cr) {
		++t[u].sum;
		return u;
	}
	int m = (cl + cr) / 2;
	if (i < m)
		t[u].l = upd(t[u].l, i, cl, m);
	else
		t[u].r = upd(t[u].r, i, m, cr);
	t[u].sum = t[t[u].l].sum + t[t[u].r].sum;
	return u;
}

int lcaw;

int get(int a, int b, int c, int k, int cl, int cr) {
	if (cl + 1 == cr)
		return cl;
	int m = (cl + cr) / 2;
	int suml = t[t[a].l].sum + t[t[b].l].sum - 2 * t[t[c].l].sum;
	if (lcaw >= cl && lcaw < m)
		++suml;
	if (suml >= k)
		return get(t[a].l, t[b].l, t[c].l, k, cl, m);
	return get(t[a].r, t[b].r, t[c].r, k - suml, m, cr);
}

void print(int v, int cl, int cr) {
	int m = (cl + cr) / 2;
	if (cl + 1 != cr)
		print(t[v].l, cl, m);
	else
		cout << cl << ' ' << t[v].sum << '\n';
	if (cl + 1 != cr)
		print(t[v].r, m, cr);
}

vi g[MX];
int w[MX];
int C;
int rt[MX];
int up[MX][PW];
int tin[MX], tout[MX], tim = 0;

void dfs(int v, int p = 0) {
	tin[v] = tim++;
	up[v][0] = p;
	for (int i = 1; i < PW; ++i)
		up[v][i] = up[up[v][i - 1]][i - 1];
	for (int to : g[v]) {
		if (to != p) {
			rt[to] = upd(rt[v], w[to], 0, C);
			dfs(to, v);
		}
	}
	tout[v] = tim;
}

bool anc(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
	if (anc(a, b))
		return a;
	if (anc(b, a))
		return b;
	for (int i = PW - 1; i >= 0; --i)
		if (!anc(up[a][i], b))
			a = up[a][i];
	return up[a][0];
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;
    vi nums(n);
    for (int i = 0; i < n; ++i) {
    	cin >> w[i];
    	nums[i] = w[i];
    }
    sort(all(nums));
    nums.resize(unique(all(nums)) - nums.begin());
    C = nums.size();
    for (int i = 0; i < n; ++i)
    	w[i] = lb(all(nums), w[i]) - nums.begin();

   	for (int i = 0; i < n - 1; ++i) {
   		int a, b;
   		cin >> a >> b;
   		--a, --b;
   		g[a].pb(b);
   		g[b].pb(a);	
   	}
   	init();
   	rt[0] = upd(0, w[0], 0, C);
   	dfs(0);
   	
   	while (q--) {
   		int a, b, k;
   		cin >> a >> b >> k;
   		--a, --b;
   		int c = lca(a, b);
   		lcaw = w[c];
   		cout << nums[get(rt[a], rt[b], rt[c], k, 0, C)] << '\n';
   	}
}
