vi primes;
primes.reserve(MX / 10 + 30);
memset(ld, -1, sizeof(int) * MX);
fi(2, MX) {
    if (ld[i] == -1) {
        primes.push_back(i);
        ld[i] = i;
    }
    fx(x, primes) {
        if (1ll * x * i >= MX || x > ld[i])
            break;
        ld[i * x] = x;
    }
}
