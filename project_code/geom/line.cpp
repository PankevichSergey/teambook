struct line {
    ld a = 0;
    ld b = 0;
    ld c = 0;
    line() = default;
    line (ld a, ld b, ld c): a(a), b(b), c(c) {}
    line(pt p1, pt p2): a(p1.y - p2.y), b(p2.x - p1.x), c(-a * p1.x - b * p1.y) {}
    ld eval(pt p) const {
        return p.x * a + p.y * b + c;
    }
    void make_normal() {
        ld norm = sqrt(a * a + b * b);
        a /= norm;
        b /= norm;
        c /= norm;
    }
    ld dist(pt p) const {
        return abs(p.x * a + p.y * b + c) / sqrt(a * a + b * b);
    }
    pt project(pt p) const {
        vec norm(a, b);
        ld sd = (p.x * a + p.y * b + c) / norm.len();
        return p + norm * (-sd / norm.len()); 
    }
    bool operator == (const line& other) const {
        return eq(a * other.b, b * other.a) &&
               eq(a * other.c, c * other.a) &&
               eq(b * other.c, c * other.b);
    }
};


bool are_parallel_lines(line f1, line f2) {
    return sgn(f1.a * f2.b - f1.b * f2.a) == 0;
}

pair<pt, int> cross_lines(line f1, line f2) {
    // 0 -- no intersection
    // 1 -- 1 point
    // 2 -- coincide 
    ld d = f1.a * f2.b - f1.b * f2.a;
    if (sgn(d) == 0) {
        return {pt(), (f1 == f2 ? 2 : 0)}
        if (f1 == f2) {
            return {pt(), 2};
        } else {
            return {pt(), 0};
        }
    }
    ld x = f1.c * f2.b - f1.b * f2.c;
    ld y = f1.a * f2.c - f1.c * f2.a;
    return {pt(x / -d, y / -d), 1};
}