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
#include <cassert>
#include <cmath>
#include <climits>
#include <queue>
#include <cstring>
#include <bitset>
#include <iomanip>


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
#ifdef LOCAL
const int MX = 201;
#else
const int MX = 1e5 + 10;
#endif
const double EPS = 1e-9;


struct nd {
	int l;
	int r;
	ll sum;
	ll add;
	nd (int _l = 0, int _r = 0, ll _sum = 0, ll _add = 0) {
		l = _l;
		r = _r;
		sum = _sum;
		add = _add;
	}
};

nd t[MX * 70];
int sz = 0;
int init() {
	assert(sz < MX * 70);
	return sz++;
}

int a[MX];

void push(int v, int cl, int cr) {
	int m = (cl + cr) / 2;
	
	int l = init();
	t[l] = t[t[v].l];
	t[l].add += t[v].add;
	t[l].sum += t[v].add * (m - cl);

	int r = init();
	t[r] = t[t[v].r];
	t[r].add += t[v].add;
	t[r].sum += t[v].add * (cr - m);

	t[v].add = 0;
	t[v].l = l;
	t[v].r = r;
}

void build(int v, int cl, int cr) {
	if (cl + 1 == cr) {
		t[v].sum = a[cl];
		return;
	}
	int m = (cl + cr) / 2;
	build(t[v].l = init(), cl, m);
	build(t[v].r = init(), m, cr);
	t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
}

void upd(int u, int l, int r, int x, int cl, int cr) {
	if (cl >= r || cr <= l)
		return;
	if (cl >= l && cr <= r) {
		t[u].add += x;
		t[u].sum += x * (cr - cl);
		return;
	}
	push(u, cl, cr);
	int m = (cl + cr) / 2;
	upd(t[u].l, l, r, x, cl, m);
	upd(t[u].r, l, r, x, m, cr);
	t[u].sum = t[t[u].l].sum + t[t[u].r].sum;
}

ll get(int v, int l, int r, int cl, int cr) {
	if (cl >= r || cr <= l)
		return 0;
	if (cl >= l && cr <= r)
		return t[v].sum;
	push(v, cl, cr);
	int m = (cl + cr) / 2;
	return get(t[v].l, l, r, cl, m) + get(t[v].r, l, r, m, cr);
}

int rt[MX];


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
    	cin >> a[i];
    build(rt[0] = init(), 0, n);
    int cur = 0;
    while (q--) {
    	char c;
    	cin >> c;
    	if (c == 'C') {
    		int l, r, x;
    		cin >> l >> r >> x;
    		--l;
    		rt[cur + 1] = init();
    		t[rt[cur + 1]] = t[rt[cur]];
    		upd(rt[cur + 1], l, r, x, 0, n);
    		++cur;
    	} else if (c == 'Q') {
    		int l, r;
    		cin >> l >> r;
    		--l;
    		cout << get(rt[cur], l, r, 0, n) << '\n';
    	} else if (c == 'H') {
    		int l, r, tn;
    		cin >> l >> r >> tn;
    		--l;
    		cout << get(rt[tn], l, r, 0, n) << '\n';
    	} else if (c == 'B') {
    		int tn;
    		cin >> tn;
    		cur = tn;
    	}
    }
}
