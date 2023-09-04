const ld PI = 4 * atan(1);
const ld EPS = 1e-9;

int sgn(ld x) {
    if (x > EPS)
        return 1;
    if (x < -EPS)
        return -1;
    return 0;
}

ld fix_angle(ld x) {
    if (x > 0)
        x = min(x, 1 - EPS);
    if (x < 0)
        x = max(x, -1 + EPS);
    return x;
}

ld mysqrt(ld x) {
    if (x < 0) return 0;
    return sqrt(x);
}

ld sqr(ld x) {
    return x * x;
}

bool eq(ld a, ld b) {
    return abs(a - b) <= EPS;
}

bool lt(ld a, ld b) {
    return a + EPS < b;
}

bool gt(ld a, ld b) {
    return a - EPS > b;
}

bool leq(ld a, ld b) {
    return a - EPS <= b;
}

bool geq(ld a, ld b) {
    return a + EPS >= b;
}