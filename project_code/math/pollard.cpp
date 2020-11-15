inline __int128 sub(__int128 a, __int128 b) {
    return a - b;
}

inline __uint128_t f(__uint128_t x) {
    return (x + 1) * (x + 1);
}

inline __int128 abs(__int128 x) {
    if (x < 0)
        return -x;
    return x;
}

ull gcd(ull a, ull b)  {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

map<ull, ull> divs;

ull pollard(ull x, ull seed = 1) {
    ull i = seed;
    ull j = seed;
    ull res = 1;
    int it = 1e5;
    while ((res == 1 || res == x) && it--) {
        i = f(i) % x;
        j = f(j) % x;
        j = f(j) % x;
        ull val = abs(sub(i, j));
        res = gcd(val, x);
    }
    return res;
}

void slow(ull x) {
    ull d = 2;
    while (d * d <= x) {
        while (x % d == 0) {
            ++divs[d];
            x /= d;
        }
        ++d;
    }
    if (x != 1)
        ++divs[x];
}

void factor(ull x) {
    if (x <= 1e12) {
        slow(x);
        return;
    }
    ull d = pollard(x);
    if (d == 1 || d == x) {
        divs[x]++;
        return;
    }
    factor(d);
    factor(x / d);
}
