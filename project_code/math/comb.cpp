struct comb {
    M f[N];
    M fr[N];
    comb() {
        f[0] = 1;
        for (int i = 1; i < N; ++i)
            f[i] = f[i - 1] * i;
        fr[N - 1] = M(1) / f[N - 1];
        for (int i = N - 2; i >= 0; --i)
            fr[i] = fr[i + 1] * (i + 1);
    }
    M C(int n, int k) {
        if (k > n || k < 0 || n < 0)
            return 0;
        return f[n] * fr[k] * fr[n - k];
    }
    M S(int n, int k, int mn) {
        if (n == 0 && k == 0) return 1;
        return C(n - (mn - 1) * k - 1, k - 1);
    }
} comb;
