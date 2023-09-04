struct cir {
    pt c;
    ld r;
    cir(pt c, ld r): c(c), r(r) {}

    cir(pt a, pt b, pt c) {
        pt mab((a.x + b.x) / 2, (a.y + b.y) / 2);
        vec ab = pt(a, b).perp();
        line l1(mab, mab + ab);

        pt mac((a.x + c.x) / 2, (a.y + c.y) / 2);
        vec ac = pt(a, c).perp();
        line l2(mac, mac + ac);

        c = cross_lines(l1, l2).first;
        r = dist(c, a);
        assert(eq(r, dist(c, a)) && eq(r, dist(c, b)) && eq(r, dist(c, c))); 
    }
    
    vector<pt> tang(pt p) {
        // returns vector of tangent points to the circle from a given point
        ld d = dist(p, c);
        if (eq(d, r)) {
            return {p};
        }
        if (leq(d, r)) {
            return {};
        }
        ld a = sqr(r) / d;
        vec v = vec(w.c, p).norm();
        pt mid = w.c + v * a;
        ld x = mysqrt(sq(r) - sq(a));
        v = v.perp();
        return {mid + v * x, mid + v * (-x)};
    }
};



vector<pt> cross_circles(cir w1, cir w2) {
    // returns all intersection points, but only 3 if circles coincide

    if (w1.r < w2.r) {
        swap(w1.c, w2.c);
        swap(w1.r, w2.r);
    }
    if (eq(w1.r, w2.r) && w1.c == w2.c) {
        return {w1.o + pt(w1.r, 0), w1.o + pt(-w1.r, 0), w1.o + pt(0, w1.r)};
    }
    ld len = dist(w1.c, w2.c);
    if (gt(len, w1.r + w2.r)|| gt(w1.r, len + w2.r)) {
        return {};
    }
    ld d = (sqr(w1.r) - sqr(w2.r) + sqr(len)) / 2 / len;
    vec v(w1.c, w2.c);
    v = v.norm();
    pt a = w1.c + v * d;
    if (eq(len, w1.r + w2.r) || eq(w1.r, w2.r + len)) {
        return {a};
    }
    v = v.ort() * sqrt(sqr(w1.r) - sqr(d));
    return {a + v, a - v};
}

vector<pt> cross_circle_line(cir w, line l) {
    // returns all the intersection points
    ld len = l.dist(w.c);
    if (lt(w.r, len)) {
        return {};
    }
    pt p = l.project(w.c);
    if (leq(w.r, len)) {
        return {p};
    }
    ld x = mysqrt(sq(w.r) - sq(len));
    vec dv = vec(-l.b, l.a).norm();
    return {p + dv * x, p + dv * (-x)};
}


vector<line> common_tangents(cir w1, cir w2) {
    // thx to igor markelov 
    vector<line> res;
    auto calc = [&](pt c, ld r1, ld r2) {
        ld r = r2 - r1;
        ld z = sqr(c.x) + sqr(c.y);
        ld d = z - sqr(r);
        if (sgn(d) == -1) return;
        d = sqrt(abs(d));
        line l;
        l.a = (c.x * r + c.y * d) / z;
        l.b = (c.y * r - c.x * d) / z;
        l.c = r1;
        ans.push_back(l);
    };
    vector<line> res;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            calc(pt(w2.c, w1.c), r1 * i, r2 * j);
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        res[i].c -= ans[i].a * w1.c.x + ans[i].b * w1.c.y;
    }
    return res;
}