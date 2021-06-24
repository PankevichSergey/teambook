__int128 myabs(__int128 x) {
    return (x < 0 ? -x : x);
}

__int128 gcd(__int128 a, __int128 b) {
    a = myabs(a);
    b = myabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct fr {
    __int128 up;
    __int128 down;
    fr(): up(0), down(1) {}
    fr(__int128 x): up(x), down(1) {}
    fr(__int128 _up, __int128 _down) {
        up = _up;
        down = _down;
        if (down < 0) {
            down *= -1;
            up *= -1;
        }
        __int128 g = gcd(up, down);
        up /= g;
        down /= g;
    }
    fr operator + (const fr & f) const {
        return fr(up * f.down + f.up * down, down * f.down);
    }
    fr operator - (const fr & f) const {
        return fr(up * f.down - f.up * down, down * f.down);
    }
    fr operator * (const fr & f) const {
        return fr(up * f.up, down * f.down);
    }
    fr operator / (const fr & f) const {
        return fr(up * f.down, down * f.up);
    }
    void operator += (const fr & f) {
        *this = *this + f;
    }
    void operator -= (const fr & f) {
        *this = *this - f;
    }
    void operator *= (const fr & f) {
        *this = *this * f;
    }
    void operator /= (const fr & f) {
        *this = *this / f;
    }
    bool operator < (const fr & f) const {
        return up * f.down < down * f.up;
    }
    bool operator == (const fr & f) const {
        return up == f.up && down == f.down;
    }
    fr operator -() const {
        return fr(-up, down);
    }
};

ostream& operator << (ostream & os, __int128 x) {
    if (x == 0) {
        os << '0';
    } else {
        if (x < 0) {
            os << '-';
            x *= -1;
        }
        string res;
        while (x) {
            res += char('0' + x % 10);
            x /= 10;
        }
        reverse(all(res));
        os << res;
    }
    return os;
}

ostream& operator << (ostream &os, const fr & f) {
    os << f.up << "/" << f.down << '\n';
    return os;
}

fr abs(const fr & f) {
    return (f.up < 0 ? -f : f);
}
