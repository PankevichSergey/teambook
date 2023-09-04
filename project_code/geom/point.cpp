struct pt {
    ld x = 0;
    ld y = 0;
    pt() = default;
    explicit pt (ld x, ld y): x(x), y(y) {
    }
    explicit pt (pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    pt perp() {
        return pt(-y, x);
    }

    pt norm() const {
        ld d = len();
        assert(sgn(d) == 1);
        return pt(x / d, y / d);
    }

    pt turn(ld a) const {
        return pt(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    ld len2() const {
        return x * x + y * y;
    }

    ld len() const {
        return sqrt(x * x + y * y);
    }

    pt operator + (pt p) const {
        return pt(x + p.x, y + p.y);
    }

    pt operator - (pt p) const {
        return pt(x - p.x, y - p.y);
    }

    ld operator * (pt p) const {
        return x * p.y - y * p.x;
    }

    ld operator ^ (pt p) const {
        return x * p.x + y * p.y;
    }

    bool operator == (const pt& rhs) const {
        return eq(x, rhs.x) && eq(y, rhs.y);
    }

    bool operator < (const pt & p) const {
        return lt(x, p.x) || (eq(x, p.x) && lt(y, p.y));
    }
};

istream& operator >> (istream & cin, pt & p) {
    cin >> p.x >> p.y;
    return cin;
} 

ostream& operator << (ostream & cout, pt & p) {
    cout << p.x << ' ' << p.y;
    return cout;
}

#define vec pt

ld dist2(pt a, pt b) {
    return pt(a, b).len2();
}

ld dist(pt a, pt b) {
    return pt(a, b).len();
}

ld ang(pt a, pt b) {
    return atan2(a * b, a ^ b);
}