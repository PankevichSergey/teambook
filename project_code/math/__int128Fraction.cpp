__int128 abs(__int128 x) {
    return (x < 0 ? -x : x);
}

__int128 gcd(__int128 a, __int128 b) {
    a = abs(a);
    b = abs(b);
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
    fr operator + (const fr & f) {
        return fr(up * f.down + f.up * down, down * f.down);
    }
    fr operator - (const fr & f) {
        return fr(up * f.down - f.up * down, down * f.down);
    }
    fr operator * (const fr & f) {
        return fr(up * f.up, down * f.down);
    }
    fr operator / (const fr & f) {
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
};
