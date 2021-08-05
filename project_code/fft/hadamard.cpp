void trans(vi & a, bool inv = false) {
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < (1 << m); ++mask) {
            if ((mask >> i) & 1) {
                int without = a[mask ^ (1 << i)]; 
                int withx = a[mask];
                if (inv) {
                    // with = old0 + old1
                    // without = old0 - old1
                    a[mask ^ (1 << i)] = add(without, withx); // old0 = (without + with) / 2
                    a[mask] = sub(withx, without); // old1 = (with - without) / 2
                } else {
                    // without + x * (withx)
                    // x in {-1, 1}
                    a[mask] = add(without, withx); // without + 1 * (withx)
                    a[mask ^ (1 << i)] = sub(without, withx); // without + (-1) * (withx)
                }
            }
        }
    }
}

void inv(vi & a) {
    trans(a, 1);
    fx(x, a) x >>= m;
}
