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
#include <unordered_map>
#include <complex>


using namespace std;

// floating point errors
// #pragma GCC optimize("Ofast,unroll-loops")

// safe
// #pragma GCC optimize("O3,unroll-loops")




// doesn't work in yandex
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// doesn't work in some judges
// #pragma GCC target(“avx2,bmi,bmi2,lzcnt,popcnt,tune=native”)

// safe
// #pragma GCC target("sse4.2,bmi,bmi2,lzcnt,popcnt")




template<typename T1, typename T2>inline void mine(T1 &x, const T2 &y) { if (y < x) x = y; }
template<typename T1, typename T2>inline void maxe(T1 &x, const T2 &y) { if (x < y) x = y; }

template<typename T1, typename T2> ostream& operator << (ostream & os, const pair<T1, T2> &b) {
    os << b.first << ' ' << b.second;
    return os;
}

template<typename T> ostream& operator << (ostream &os, const vector<T> &b) {
    for (const auto &k : b) os << k << ' ';
    return os;
}

template<typename T> istream& operator >> (istream &is, vector<T> &b) {
    for (auto &k : b) is >> k;
    return is;
}

template<typename T> ostream& operator << (ostream &os, const set<T> & b) {
    for (const auto &k : b) os << k << ' ';
    return os;
}


void dbg_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
  cerr << "   " << H;
  dbg_out(T...);
}
 
#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif




#define pb push_back
#define eb emplace_back
#define ppb pop_back()
#define mp make_pair
#define fi first;
#define se second;
#define fr front()
#define bc back()
#define fx(x, a) for (auto& x : a)
#define siz(x) (long long)x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define left leftkekmda
#define right rightkekmda

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using str = string;

template<typename T> using V = vector<T>; 

using vi = V<int>;
using vl = V<ll>;
using vch = V<char>;
using vpii = V<pii>;
using vvi = V<vi>;
using vvl = V<vl>;
using vvch = V<vch>;




template<typename T>
int Bit(T x, int sh) {
    return (x >> sh) & 1;
}
template<typename T>
int Bits(T x) {
    return __builtin_popcountll(x);
}
template<typename T>
int FirstBit(T x) {
    return __builtin_ctzll(x);
}
template<typename T>
int LastBit(T x) {
    return 63 - __builtin_clzll(x);
}

ll div_up(ll a, ll b) { return a/b+((a^b)>0&&a%b); }
ll div_down(ll a, ll b) { return a/b-((a^b)<0&&a%b); }



mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());




void solve() {
    
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int test_ = 1;
    //cin >> test_;
    while (test_--) solve();
}
