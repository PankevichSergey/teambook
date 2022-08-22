struct Line {
    int k;
    int b;
    Line(int k, int b): k(k), b(b) {}
    long long get(int x) const {
        return 1ll * k * x + b;
    }
    int better(Line rhs) const {
        int db = rhs.b - b;
        int dk = k - rhs.k;
        if (dk < 0) {
            dk *= -1;
            db *= -1;
        }
        assert(dk != 0);
        return db / dk + ((db ^ dk) > 0 && db % dk);
    }
};


class LiChao {
public:
    enum Type {
        MIN,
        MAX
    };
    const static long long NEUTRAL = ;
    const static int min_x = ;
    const static int max_x = ;
    const static Type type = ;

private:
    struct nd {
        nd* l;
        nd* r;
        Line line;
        int size;
        nd(nd* l, nd* r, Line line, int size): l(l), r(r), line(line), size(size) {}
    };

    static int getSize(nd* v) {
        if (!v) {
            return 0;
        }
        return v->size;
    }

    nd * rt;

    void add(nd* v, Line l, int cl, int cr) {
        int cm = (cl + cr) / 2;
        bool left = (type == MIN ? l.get(cl) < v->line.get(cl) : l.get(cl) > v->line.get(cl));
        bool mid = (type == MIN ? l.get(cm) < v->line.get(cm) : l.get(cm) > v->line.get(cm));
        if (mid) {
            swap(v->line, l);
        }
        if (cl + 1 == cr) {
            return;
        }
        if (left ^ mid) {
            if (v->l) add(v->l, l, cl, cm);
            else v->l = new nd(nullptr, nullptr, l, 1);
        } else {
            if (v->r) add(v->r, l, cm, cr);
            else v->r = new nd(nullptr, nullptr, l, 1);
        }
    }

    long long get(nd* v, int x, int cl, int cr) const {
        if (!v) return NEUTRAL;
        long long res = v->line.get(x);
        int cm = (cl + cr) / 2;
        if (x < cm) return (type == MIN ? min(res, get(v->l, x, cl, cm)) : max(res, get(v->l, x, cl, cm)));
        return (type == MIN ? min(res, get(v->r, x, cm, cr)) : max(res, get(v->r, x, cm, cr)));
    }

    void getLinesDfs(nd* v, vector<Line>& lines) const {
        if (!v) return;
        lines.push_back(v->line);
        getLinesDfs(v->l, lines);
        getLinesDfs(v->r, lines);
    }
    void mergeDfs(nd* to, nd* from) {
        if (!from) return;
        add(to, from->line, min_x, max_x);
        mergeDfs(to, from->l);
        mergeDfs(to, from->r);
    }
public:
    LiChao(): rt(nullptr) {}
    explicit LiChao(Line line) {
        rt = new nd(nullptr, nullptr, line, 1);
    }
    explicit LiChao(const vector<Line>& lines) {
        rt = nullptr;
        for (Line line : lines) {
            add(line);
        }
    }
    long long get(int x) const {
        if (rt) {
            return get(rt, x, min_x, max_x);
        }
        throw;
    }
    void add(Line l) {
        if (!rt) {
            rt = new nd(nullptr, nullptr, l, 1);
        } else {
            add(rt, l, min_x, max_x);
        }
    }
    vector<Line> getLines() const {
        vector<Line> result;
        result.reserve(getSize(rt));
        getLinesDfs(rt, result);
        return result;
    }

    static LiChao merge(LiChao lhs, LiChao rhs) {
        if (getSize(lhs.rt) < getSize(rhs.rt)) {
            swap(lhs, rhs);
        }
        lhs.mergeDfs(lhs.rt, rhs.rt);
        return lhs;
    }
};