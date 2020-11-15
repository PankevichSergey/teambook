ll add(ll a, ll b) {
	a += b;
	if (a >= MOD) return a - MOD;
	return a;
}

ll sub(ll a, ll b) {
	a -= b;
	if (a < 0) return a + MOD;
	return a;
}

ll mult(ll a, ll b) {
	return a * b % MOD;
}

ll powmod(ll a, ll p) {
	if (p == 0) return 1;
	if (p & 1) return mult(a, powmod(a, p - 1));
	return powmod(mult(a, a), p / 2);
}

ll rev(ll a) {
	return powmod(a, MOD - 2);
}
