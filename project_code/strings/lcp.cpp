int lcp[MX];
int pos[MX];
void build_lcp(str s) {
    s += '#';
    int n = siz(s);
    fi(0, n)
        pos[p[i]] = i;
    int cur = 0;
    fi(0, n) {
        if (pos[i] == n - 1)
            continue;
        cur = max(0, cur - 1);
        int j = p[pos[i] + 1];
        int sz = min(n - i, n - j);
        while (cur < sz && s[i + cur] == s[j + cur])
            ++cur;
        lcp[pos[i]] = cur;
    }
}
