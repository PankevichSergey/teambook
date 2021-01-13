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

template<typename T>ostream& operator << (ostream &out, const vector<T> &b) {
    for (auto k : b) out << k << ' ';
    return out;
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



const int MOD = 1000000007;
const int INF = 1000000050;
const long long BIG = (long long)2e18 + 50;
const int MX = 200010;
const double EPS = 1e-9;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
