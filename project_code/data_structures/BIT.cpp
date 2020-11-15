int BIT[MX];

inline void add(int i, int x) {
    for (; i < MX; i += i & -i)
        BIT[i] += x;
} 

inline int get(int i) {
    int ans = 0;
    for (; i > 0; i -= i & -i)
        ans += BIT[i];
    return ans;
}

inline int getlr(int l, int r) {
    return get(r) - get(l - 1);
}

inline int lastless(int x) {
    int i = 0;
    for (int pw = PW - 1; pw >= 0; --pw) {
        if (i + (1 << pw) <= n && x > BIT[i + (1 << pw)]) {
            i += 1 << pw;
            x -= BIT[i];
        }
    }
    return i;
}
