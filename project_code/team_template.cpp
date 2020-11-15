/*
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
*/

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

#ifdef LOCAL
    #define dbg(x) cout << #x << " : " << x << endl;
#else
    #define dbg(x)
#endif


#define int long long
#define pb push_back
#define ppb pop_back()
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define siz(a) (int)a.size()
#define fi first
#define se second
#define cinv(v) for (auto& x: v) cin >> x

template <typename T1, typename T2> inline bool chkmin(T1 &x, const T2 &y) {if (x > y) {x = y; return 1;} return 0;}
template <typename T1, typename T2> inline bool chkmax(T1 &x, const T2 &y) {if (x < y) {x = y; return 1;} return 0;}

#define mine chkmin
#define maxe chkmax

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<ch> vch;
typedef vector<str> vs;

const int MOD = (int)1e9 + 7;
const int INF = (int)1e9 + 50;
const long long BIG = (long long)2e18 + 50;
const int MX = 200010;
const double EPS = 1e-9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


ostream& operator<< (ostream &out, const vi &b) {
    for (auto k : b) out << k << " ";
    return out;
}

istream& operator>> (istream& in, pii& b) {
    in >> b.first >> b.second;
    return in;
}

ostream& operator<< (ostream& out, const pii& b) {
    out << "{" << b.first << ", " << b.second << "}";
    return out;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
