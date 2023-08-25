vector<int> pf(string& s) {
    int n = s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; ++i) {
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
