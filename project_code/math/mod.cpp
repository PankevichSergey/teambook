//const int MOD = 1e9 + 7;
//const int N = ;
namespace md {
    ll mod(ll n) {
        if (n <= -MOD || n >= MOD) n %= MOD;
        if (n < 0) return n + MOD;
        else return n;
    }

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
}

struct M {
    ll x;
    M (ll _x) { x = md::mod(_x); }
    M () { x = 0; }
    M operator + (M y) const {
        return M(md::add(x, y.x));
    }
    M operator - (M y) const {
        return M(md::sub(x, y.x));
    }
    M operator * (M y) const { return md::mult(x, y.x); }
    M operator / (M y) const { return md::mult(x, md::rev(y.x)); }
    M operator + (ll y) { return (*this) + M(y); }
    M operator - (ll y) { return (*this) - M(y); }
    M operator * (ll y) { return (*this) * M(y); }
    M operator / (ll y) { return (*this) / M(y); }
    M operator ^ (ll y) const { return M(x ^ y); }
    void operator += (M y) { *this = *this + y; }
    void operator -= (M y) { *this = *this - y; }
    void operator *= (M y) { *this = *this * y; }
    void operator /= (M y) { *this = *this / y; }
    void operator += (ll y) { *this = *this + y; }
    void operator -= (ll y) { *this = *this - y; }
    void operator *= (ll y) { *this = *this * y; }
    void operator /= (ll y) { *this = *this / y; }
    void operator ^= (ll y) { *this = *this ^ y; }
    bool operator == (M y) const { return x == y.x; }
    bool operator < (M y) const { return x < y.x; }
};

M operator * (ll x, const M &y) {return y * x;}
M operator + (ll x, const M &y) {return y + x;}
M operator - (ll x, const M &y) {return M(x) - y;}
M operator / (ll x, const M &y) {return M(x) / y;}

ostream& operator << (ostream& os, const M &a) {
    os << a.x;
    return os;
}

istream& operator >> (istream& is, M &a) {
    ll x;
    is >> x;
    a = M(x);
    return is;
}
