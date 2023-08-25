vector<int> zfunc(str & s) {
    int n = s.size();
    vector<int> z(n, 0);
    int r = -1, l = 0;
    for (int i = 1; i < n; ++i) {
        z[i] = max(0, min(r - i + 1, z[i - l]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}
