int l = 0, r = 0;
fi(0, n) {
    if (r >= i)
        d1[i] = min(r - i + 1, d1[l + r - i]);
    while (i + d1[i] < n && i - d1[i] >= 0 && s[i + d1[i]] == s[i - d1[i]])
        ++d1[i];
    if (i + d1[i] - 1 > r) {
        r = i + d1[i] - 1;
        l = i - d1[i] + 1;
    }
}
l = 0, r = -1;
fi(0, n) {
    if (r >= i)
        d2[i] = min(r - i + 1, d2[l + r - i + 1]);
    while (i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i + d2[i]] == s[i - 1 - d2[i]])
        ++d2[i];
    if (i + d2[i] - 1 > r) {
        r = i + d2[i] - 1;
        l = i - d2[i];
    }
}
