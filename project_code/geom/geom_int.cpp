struct pt {
    int x;
    int y;
    pt (int _x = 0, int _y = 0) {
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
    ll len2() {
        return x * x + y * y;
    }
    double len() {
        return sqrt(len2());
    }
    pt operator + (pt p) {
        return pt(x + p.x, y + p.y);
    }
    ll operator * (pt p) {
        return x * p.y - y * p.x;
    }
    ll operator ^ (pt p) {
        return x * p.x + y * p.y;
    }
    bool operator < (const pt & p) const {
        return mp(x, y) < mp(p.x, p.y);
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


ll dist2(pt a, pt b) {
    return pt(a, b).len2();
}

double dist(pt a, pt b) {
    return sqrt(dist2(a, b));
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
    if (a * b == 0)
        return a.len2() < b.len2();
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
    }
    return hull;
}

struct line {
    int a;
    int b;
    int c;
    line (int _a = 0, int _b = 0, int _c = 0) {
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

struct cir {
    pt C;
    double r;
    cir (pt _C, double _r) {
        C = _C;
        r = _r;
    }
};
