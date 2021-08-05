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
#define fx(x, a) for (auto& x : a)
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
template<typename T1, typename T2> ostream& operator << (ostream & os, const pair<T1, T2> &b) {
    os << b.first << ' ' << b.second;
    return os;
}


typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef string str;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<char> vch;
typedef vector<str> vs;




mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}
