// const int ALP = 256;
// const int LOG = 18;
 
struct Sufarr {
    int cnt[N];
    int c[N];
    int cn[N];
    int p[N];
    int pn[N];
    int classes;
    int lcp[N];
    int pos[N];
    int n;
    int st[LOG][N];
    int pw2[N];
	
    void BuildSparse() {
        for (int i = 0; i < n; ++i) {
            st[0][i] = lcp[i];
        }
        for (int i = 1; i < LOG; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
        pw2[1] = 0;
        for (int i = 2; i < N; ++i) {
            pw2[i] = pw2[i - 1] + 1;
            if (i < (1 << pw2[i])) {
                --pw2[i];
            }
        }
    }
 
    inline int getlcp(int l, int r) { // 0-based interval
        int k = pw2[r - l];
        return min(st[k][l], st[k][r - (1 << k)]);
    }
 
    void Init(str s) {
        s += '#';
        n = s.size();
        for (char x : s) {
            ++cnt[x];
        }
        partial_sum(cnt, cnt + ALP, cnt);
        for (int i = 0; i < n; ++i) {
            p[--cnt[s[i]]] = i;
        }
        classes = 1;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i - 1]]) ++classes;
            c[p[i]] = classes - 1;
        }
        for (int k = 0; (1 << k) < n; ++k) {
            memset(cnt, 0, classes * sizeof(int));
            for (int i = 0; i < n; ++i) {
                pn[i] = p[i] - (1 << k);
                if (pn[i] < 0)
                    pn[i] += n;
                ++cnt[c[i]];
            }
            partial_sum(cnt, cnt + classes, cnt);
            for (int i = n - 1; i >= 0; --i) {
                p[--cnt[c[pn[i]]]] = pn[i];
            }
            classes = 1;
            cn[p[0]] = 0;
            for (int i = 1; i < n; ++i) {
                int lw = p[i - 1];
                int rw = lw + (1 << k);
                int l = p[i];
                int r = l + (1 << k);
                if (rw >= n) rw -= n;
                if (r >= n) r -= n;
 
                classes += c[l] != c[lw] || c[r] != c[rw];
                cn[p[i]] = classes - 1;
            }
            memcpy(c, cn, n * sizeof(int));
        }
 
 
        for (int i = 0; i < n; ++i) {
            pos[p[i]] = i;
        }
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (pos[i] == n - 1) {
                continue;
            }
            --cur;
            if (cur < 0) cur = 0;
            int j = p[pos[i] + 1];
            int sz = min(n - i, n - j);
            while (cur < sz && s[i + cur] == s[j + cur]) {
                ++cur;
            }
            lcp[pos[i]] = cur;
        }
        
        BuildSparse();
    }
}suf;
