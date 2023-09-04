vector<pt> build_hull(vector<pt> pts) {
    int n = pts.size();
    pt p = pts[0];
    for (int i = 0; i < n; ++i) {
        mine(p, pts[i]);
    }
    for (int i = 0; i < n; ++i) {
        pts[i] = pt(p, pts[i]);
    }
    sort(all(pts), [&](pt a, pt b){
        if (eq(a * b, 0)) {
            return a.len2() < b.len2();
        }
        return a * b > 0;
    });
    vector<pt> hull = {pts[0]};
    for (int i = 1; i < n; ++i) {
        while (hull.size() > 1) {
            if (leq(vec(hull[siz(hull) - 2], hull.back()) * vec(hull.back(), pts[i]), 0)) {
                hull.ppb;
            } else {
                break;
            }
        }
        hull.pb(pts[i]);
    }
    for (auto&x : hull) {
        x = x + p;
    }
    return hull;
}

ld diameter(vector<pt> p) {
    p = build_hull(p);
    int n = p.size();
    if (n <= 1) {
        return 0;
    }
    if (n == 2) {
        return dist(p[0], p[1]);
    }
    ld ans = 0;
    int i = 0, j = 1;
    while (i < n) {
        while (sign((p[(i + 1) % n] - p[i]) ^ (p[(j + 1) % n] - p[j])) >= 0) {
            maxe(ans, dist(p[i], p[j]));
            j = (j + 1) % n;
        }
        maxe(ans, pt(p[i], p[j]).len());
        ++i;
    }
    return ans;
}


ld perimeter(const vector<pt>& p) {
  ld ans = 0;
  for (int i = 0; i < p.size(); ++i) {
    ans += pt(p[i], p[i + 1 < p.size() ? i + 1 : 0]).len();
  }
  return ans;
}

ld area(const vector<pt>& p) {
    ld res = 0;
    for (int i = 0; i < p.size(); ++i) {
        res += p[i] * p[(i + 1 < p.size() ? i + 1 : 0)];
    }
    return abs(res) / 2;
}


bool is_convex(const vector<pt>& p) {
    // allows 3 points on one line
    int n = p.size();
    int was = 0;
    for (int i = 0; i < n; ++i) {
        int pr = (i == 0 ? n - 1 : i - 1);
        int nx = (i + 1 == n ? 0 : i + 1);
        int cur = sgn(vec(p[pr], p[i]) * vec(p[i], p[nx]));
        if (was && cur && was != cur) {
            return false;
        }
        if (cur) was = cur;
    }
    return true;
}

bool is_in_poly_fast(vector<pt>& p, pt a, bool allow_bound) {
    // static const int ADDP = 1e9;    
    int n = p.size();
    bool sum = false;
    pt b = a + pt(ADDP, 1);
    for (int i = 0; i < n; ++i) {
        pt l = p[i];
        pt r = p[i + 1 == n ? 0 : i + 1];
        if (is_on_seg(l, r, a)) {
            return allow_bound;
        }
        sum ^= are_crossed(a, b, l, r);
    }
    return sum;
}


bool is_in_poly_slow(vector<pt>& p, pt a, bool allow_bound) {
    int n = p.size();
    ld sum = 0;
    for (int i = 0; i < n; ++i) {
        pt l = p[i];
        pt r = p[i + 1 == n ? 0 : i + 1];
        if (is_on_seg(l, r, a)) {
            return allow_bound;
        }
        sum += ang(vec(a, l), vec(a, r));
    }
    return abs(sum) > PI / 2;
}

bool is_in_angle(pt a, pt o, pt b, pt p) {
    // works for non degenerate angle
    if (vec(o, a) * vec(o, b) < 0) {
        swap(a, b);
    }
    vec oa(o, a);
    vec op(o, p);
    vec ob(o, b);
    return sgn(oa * op) >= 0 && sgn(op * ob) >= 0;
} 

bool is_in_triangle(pt a, pt b, pt c, pt p) {
    // works for non degenerate triangle
    return is_in_angle(c, a, b, p) && is_in_angle(a, b, c, p);
}


bool is_in_convex_poly(vector<pt>& p, pt a) {
    // works for non degenerate convex polygon in counterclockwise order
    int n = p.size();
    if (lt(vec(p[0], p[1]) * vec(p[0], a), 0)) return false;
    if (gt(vec(p[0], p[n - 1]) * vec(p[0], a), 0)) return false;
    int L = 1;
    int R = n - 1;
    while (R - L > 1) {
        int mid = (L + R) / 2;
        if (is_in_angle(p[1], p[0], p[mid], a)) {
            R = mid;
        } else {
            L = mid;
        }
    }
    return is_in_triangle(p[0], p[L], p[R], a);
}


pair<int, int> tangents_alex(vector<Point>& p, Point& a) {
// thx to alex nekrasov 
    int n = p.size();
    int l = __lg(n);
    auto findWithSign = [&](int val) {
        int i = 0;
        for (int k = l; k >= 0; --k) {
        int i1 = (i - (1 << k) + n) % n;
        int i2 = (i + (1 << k)) % n;
        if (sgn(vec(a, p[i1]) * vec(a, p[i])) == val) i = i1;
        if (sgn(vec(a, p[i2]) * vec(a, p[i])) == val) i = i2;
        }
        return i;
    };
    return {findWithSign(1), findWithSign(-1)};
}