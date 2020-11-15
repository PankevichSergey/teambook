vi pf(str &s) {
    int n = s.size();
    vi p(n, 0);
    fi(1, n) {
        int cur = i - 1;
        while (cur >= 0) {
            if (s[i] == s[p[cur]]) {
                p[i] = p[cur] + 1;
                break;
            }
            cur = p[cur] - 1;
        }
    }
    return p;
}
