#include <vector>

using namespace std;
using ull = unsigned long long;

struct bs {
    vector<ull> a;
    int n;
    bs() {
        a = {};
        n = 0;
    }
    bs(int ns): n(ns) {
        if (n % 64) {
            n += 64 - n % 64;
        }
        n /= 64;
        a.resize(n, 0);
    }
    void reset() {
        for (ull& x : a) {
            x = 0;
        }
    }
    void set(int i, int x) {
        int block = i >> 6;
        ull val = 1ull << (i & 63);
        a[block] &= ~val;
        if (x) a[block] ^= val;
    }
    bool operator[] (int i) const {
        return (a[i >> 6] >> (i & 63)) & 1;
    }
    int count() const {
        int res = 0;
        for (ull x : a) {
            res += __builtin_popcountll(x);
        }
        return res;
    }
    bool empty() const {
        for (ull x : a) {
            if (x != 0) {
                return false;
            }
        }
        return true;
    }
    bool have_intersection(const bs& rhs) const {
        for (int i = 0; i < n; ++i) {
            if (a[i] & rhs.a[i]) {
                return true;
            }
        }
        return false;
    }
    bs& operator = (const bs& rhs) {
        n = rhs.n;
        a = rhs.a;
        return *this;
    }
    bs operator & (const bs& rhs) const {
        bs res(n * 64);
        for (int i = 0; i < n; ++i) {
            res.a[i] = a[i] & rhs.a[i];
        }
        return res;
    }
    bs operator | (const bs& rhs) const {
        bs res(n * 64);
        for (int i = 0; i < n; ++i) {
            res.a[i] = a[i] | rhs.a[i];
        }
        return res;
    }
    bs operator ^ (const bs& rhs) const {
        bs res(n * 64);
        for (int i = 0; i < n; ++i) {
            res.a[i] = a[i] ^ rhs.a[i];
        }
        return res;
    }
    void operator &= (const bs& rhs) {
        for (int i = 0; i < n; ++i) {
            a[i] &= rhs.a[i];
        }
    }
    void operator |= (const bs& rhs) {
        for (int i = 0; i < n; ++i) {
            a[i] |= rhs.a[i];
        }
    }
    void operator ^= (const bs& rhs) {
        for (int i = 0; i < n; ++i) {
            a[i] ^= rhs.a[i];
        }
    }
    int find_first() const {
        int ans = 0;
        for (ull x : a) {
            if (x == 0) {
                ans += 64;
            } else {
                return ans + __builtin_ctzll(x);
            }
        }
        return ans;
    }
    int find_next(int i) const {
        int block = i >> 6;
        if (block >= n) {
            return n * 64;
        }
        {
            ull x = a[block];
            i &= 63;
            x >>= (i + 1);
            if (x != 0) {
                return block * 64 + (i + 1) + __builtin_ctzll(x);
            }
        }
        for (int i = block + 1; i < n; ++i) {
            if (a[i] != 0) {
                return i * 64 + __builtin_ctzll(a[i]);
            }
        }
        return 64 * n;
    } 
    
};