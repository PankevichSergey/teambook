bool is_on_seg(pt a, pt b, pt c) {
    if (a == b) {
        return a == c;
    }
    vec ab(a, b);
    vec ac(a, c);
    vec ba(b, a);
    vec bc(b, c);
    return sgn(ab * ac) == 0 && sgn(ab ^ ac) >= 0 && sgn(ba ^ bc) >= 0;
}

bool are_crossed(ld l1, ld r1, ld l2, ld r2) { 
    // at least one common point
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return geq(min(r1, r2), max(l1, l2));
}



bool are_crossed(pt a, pt b, pt c, pt d) {
    // at least one common point
    if (!are_crossed(a.x, b.x, c.x, d.x)) return false;
    if (!are_crossed(a.y, b.y, c.y, d.y)) return false;
    vec ab(a, b);
    vec ac(a, c);
    vec ad(a, d);
    if (sgn(ab * ac) * sgn(ab * ad) == 1) return false;
    vec cd(c, d);
    vec ca(c, a);
    vec cb(c, b);
    if (sgn(cd * ca) * sgn(cd * cb) == 1) return false;
    return true;
}   


pair<pt, bool> intersect_segments(pt a, pt b, pt c, pt d) {
    if (a == b) {
        if (is_on_seg(c, d, a)) {
            return {a, true};
        } else {
            return {pt(), 0};
        }
    }
    if (c == d) {
        return intersect_segments(c, d, a, b);
    }

    vec ab(a, b);
    vec ac(a, c);
    vec ad(a, d);
    if (eq(ab * ac, 0) && eq(ab * ad, 0)) {
        for (int i = 0; i < 2; ++i) {
            if (is_on_seg(a, b, c)) return {c, true};
            if (is_on_seg(a, b, d)) return {d, true};
            swap(a, c);
            swap(b, d);
        }
        return {pt(), false};
    }
    auto res = cross_lines(line(a, b), line(c, d));
    assert(res.second != 2);
    if (res.second == 0) {
        return res;
    }
    if (is_on_seg(a, b, res.first) && is_on_seg(c, d, res.first)) {
        return res;
    }
    return {pt(), 0};
}
