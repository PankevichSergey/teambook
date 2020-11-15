int sgn(double x) {
    if (x > EPS)
        return 1;
    if (x < -EPS)
        return -1;
    return 0;
}

double fix(double x) {
    if (x > 0)
        x = min(x, 1 - EPS);
    if (x < 0)
        x = max(x, -1 + EPS);
    return x;
}

bool eq(double a, double b) {
    return abs(a - b) < EPS;
}

bool lt(double a, double b) {
    return a + EPS < b;
}

bool mt(double a, double b) {
    return a - EPS > b;
}


struct pt {
    double x;
    double y;
    pt (double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }

    pt (pt a, pt b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    pt perp() {
        return pt(-y, x);
    }

    pt turn(double a) {
        return pt(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    double len() {
        return sqrt(x * x + y * y);
    }

    pt operator + (pt p) {
        return pt(x + p.x, y + p.y);
    }

    double operator * (pt p) {
        return x * p.y - y * p.x;
    }

    double operator ^ (pt p) {
        return x * p.x + y * p.y;
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

double dist(pt a, pt b) {
    return pt(a, b).len();
}

double ang(pt a, pt b) {
    return atan2(a * b, a ^ b);
}

double segdist(pt a, pt b, pt c) {
    double res = min(dist(a, c), dist(b, c));
    vec ab(a, b);
    vec ac(a, c);
    vec ba(b, a);
    vec bc(b, c);   
    if ((ab ^ ac) > 0 && (ba ^ bc) > 0) 
        return abs(ac * bc) / dist(a, b);
    return res;
}

bool cmp(pt a, pt b) {
    if (eq(a * b, 0))
        return a.len() < b.len();
    return a * b > 0;
}

vector<pt> build_hull(vector<pt> pts) {
    int n = pts.size();
    pt p = pts[0];
    fi(0, n)
        mine(p, pts[i]);
    fi(0, n)
        pts[i] = pt(p, pts[i]);
    sort(all(pts), cmp);
    vector<pt> hull = {pts[0]};
    fi(1, n) {
        while (hull.size() > 1) {
            if (pt(hull[siz(hull) - 2], hull.back()) * pt(hull.back(), pts[i]) < EPS) 
                hull.ppb;
            else
                break;
        }
        hull.pb(pts[i]);
    }
    fx(x, hull) {
        x = x + p;
        dbg(x);
    }
    return hull;
}

struct line {
    double a;
    double b;
    double c;
    line (double _a = 0, double _b = 0, double _c = 0) {
        a = _a;
        b = _b;
        c = _c;
    }
    line(pt p1, pt p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
    }
    double dist(pt p) {
        return abs(p.x * a + p.y * b + c) / sqrt(a * a + b * b);
    }
};

pt inter(line f1, line f2) {
    double x = f1.c * f2.b - f1.b * f2.c;
    double y = f1.a * f2.c - f1.c * f2.a;
    double d = f1.a * f2.b - f1.b * f2.a;
    return pt(x / -d, y / -d);
}

struct cir {
    pt C;
    double r;

    cir (pt _C, double _r) {
        C = _C;
        r = _r;
    }

    cir (pt a, pt b, pt c) {
        pt mab((a.x + b.x) / 2, (a.y + b.y) / 2);
        vec ab = pt(a, b).perp();
        line l1(mab, mab + ab);

        pt mac((a.x + c.x) / 2, (a.y + c.y) / 2);
        vec ac = pt(a, c).perp();
        line l2(mac, mac + ac);

        C = inter(l1, l2);
        r = dist(C, a);
        assert(eq(r, dist(C, a)) && eq(r, dist(C, b)) && eq(r, dist(C, c))); 
    }
    
    vector<pt> tang(pt p) {
        double d = dist(p, C);
        if (eq(r, d))
            return {p};
        double L = sqrt(d * d - r * r);
        double a = acos(fix(L / d));
        vec pc(p, C);
        pc = pc * (L / d);
        return {p + pc.turn(a), p + pc.turn(-a)};
    }
};
