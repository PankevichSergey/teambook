template<typename T>
struct PushSegTree {
    struct inf {
        #warning SET NEUTRAL
        static const T N_ADD = 0;
        static const T N_VAL = 0;
        T add;
        T val;
        inf(): add(N_ADD), val(N_VAL) {}
        inf(T x): add(N_ADD), val(x) {}
        T merge(const T& left, const T& right);
        inf(inf left, inf right): add(N_ADD) {
            val = merge(left.val, right.val);
        }
        void apply(T x);
    };
    inf t[4 * N];
    #warning CALL BUILD!!!
    void build(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = inf(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * v, l, mid);
        build(2 * v + 1, mid, r);
        t[v] = inf(t[2 * v], t[2 * v + 1]);
    }
    void push(int v) {
        if (t[v].add != inf::N_ADD) {
            t[2 * v].apply(t[v].add);
            t[2 * v + 1].apply(t[v].add);
            t[v].add = inf::N_ADD;   
        }
    }
    inf getlr(int v, int l, int r, int cl, int cr) {
        if (cl >= r || cr <= l) return inf();
        if (cl >= l && cr <= r) return t[v];
        push(v);
        int mid = (cl + cr) / 2;
        return inf(getlr(2 * v, l, r, cl, mid), getlr(2 * v + 1, l, r, mid, cr));
    }
    inf get(int v, int i, int cl, int cr) {
        if (cl + 1 == cr) return t[v];
        push(v);
        int mid = (cl + cr) / 2;
        if (i < mid) return get(2 * v, i, cl, mid);
        return get(2 * v + 1, i, mid, cr);
    }
    void updlr(int v, int l, int r, T x, int cl, int cr) {
        if (cl >= r || cr <= l) return;
        if (cl >= l && cr <= r) {
            t[v].apply(x);
            return;
        }
        push(v);
        int mid = (cl + cr) / 2;
        updlr(2 * v, l, r, x, cl, mid);
        updlr(2 * v + 1, l, r, x, mid, cr);
        t[v] = inf(t[2 * v], t[2 * v + 1]);
    }
    void upd(int v, int i, T x, int cl, int cr) {
        if (cl + 1 == cr) {
            t[v] = inf(x);
            return;
        }
        push(v);
        int mid = (cl + cr) / 2;
        if (i < mid) upd(2 * v, i, x, cl, mid);
        else upd(2 * v + 1, i, x, mid, cr);
        t[v] = inf(t[2 * v], t[2 * v + 1]);
    }
};
