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
const int MX = 100010;
const double EPS = 1e-9;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int a[MX];

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

nd t[MX * 20];
int rt[MX];

int sz = 0;
int init() {
	t[sz] = nd();
	return sz++;
}

int get(int v1, int v2, int k, int cl, int cr) {
	if (cl + 1 == cr)
		return cl;
	int m = (cl + cr) / 2;
	int sumleft = t[t[v2].l].sum - t[t[v1].l].sum;
	if (sumleft >= k)
		return get(t[v1].l, t[v2].l, k, cl, m);
	return get(t[v1].r, t[v2].r, k - sumleft, m, cr);
}

int upd(int v, int i, int cl, int cr) {
	int u = init();
	if (cl + 1 == cr) {
		t[u].sum = t[v].sum + 1;
		return u;
	}
	t[u] = t[v];
	int m = (cl + cr) / 2;
	if (i < m) {
		t[u].l = upd(t[v].l, i, cl, m);
	} else {
		t[u].r = upd(t[v].r, i, m, cr);
	}
	t[u].sum = t[t[u].l].sum + t[t[u].r].sum;
	return u;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;
    vi nums(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    	nums[i] = a[i];
    }
    sort(all(nums));
    nums.resize(unique(all(nums)) - nums.begin());
   	int m = nums.size();
    for (int i = 0; i < n; ++i)
    		a[i] = lb(all(nums), a[i]) - nums.begin();
    rt[0] = init();
    for (int i = 1; i <= n; ++i) {
    	rt[i] = upd(rt[i - 1], a[i - 1], 0, m);
    }

    while (q--) {
    	int l, r, k;
    	cin >> l >> r >> k;
    	--l;
    	cout << nums[get(rt[l], rt[r], k, 0, m)] << '\n';
    }
}
