struct bit2 {
    struct bit {
        vector<int> cords;
        vector<int> f;
        bit() = default;
        bit(vector<int> crd): cords(crd) {
            sort(cords.begin(), cords.end());
            cords.resize(unique(cords.begin(), cords.end()) - cords.begin());
            f.resize(cords.size() + 1, 0);
        }
        int getleq(int x) {
            int res = 0;
            auto it = upper_bound(cords.begin(), cords.end(), x) - cords.begin() - 1;
            for (int i = it + 1; i > 0; i -= i & -i) {
                res += f[i];
            }
            return res;
        }
        int get(int l, int r) {
            return getleq(r) - getleq(l);
        }
        void add(int x, int delta) {
            auto it = lower_bound(cords.begin(), cords.end(), x) - cords.begin();
            for (int i = it + 1; i < f.size(); i += i & -i) {
                f[i]  += delta;
            }
        }
    };
    vector<vector<int>> dots;
    vector<bit> bits;
    bit2(int n) {
        dots.resize(n + 1);
        bits.resize(n + 1);
    }
    void adddt(int x, int y) {
        dots[x].push_back(y);
    }
    void build() {
        for (int i = 1; i < bits.size(); ++i) {
            vector<int> cords;
            for (int j = (i - (i & -i)) + 1; j <= i; ++j) {
                for (int x : dots[j]) {
                    cords.push_back(x);
                }
            }
            bits[i] = bit(cords);
        }
    }

    void add(int x, int y, int d) {
        for (int i = x; i < bits.size(); i += i & -i) {
            bits[i].add(y, d);
        }
    }
    int get(int r, int ly, int ry) {
        int res = 0;
        for (int i = r; i > 0; i -= i & -i) {
            res += bits[i].get(ly, ry);
        }
        return res;
    }
    int get(int lx, int rx, int ly, int ry) {
        return get(rx, ly, ry) - get(lx, ly, ry);
    }
};
