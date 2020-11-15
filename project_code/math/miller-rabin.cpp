mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll mult(ll a, ll b, ll mod) {
	__int128 res = a;
	res *= b;
	return res % mod;
}


ll pw(ll a, ll b, ll mod) {
	if (b == 0) return 1;
	if (b & 1) return mult(a, pw(a, b - 1, mod), mod);
	return pw(mult(a, a, mod), b / 2, mod);	
}


bool is_prob_prime(ll x, int iters) {
	if (x == 1)
		return false;
	if (x == 2)
		return true;
	if ((x & 1) == 0)
		return false;
	int k = __builtin_ctzll(x - 1);
	ll m = (x - 1) / (1 << k);
	for (int it = 0; it < iters; ++it) {
		ll num = rng() % (x - 1) + 1;
		ll cur = pw(num, m, x); 
		if (cur == 1 || cur == x - 1)
			continue;
		bool good = false;
		for (int pw2 = 1; pw2 < k; ++pw2) {
			cur = mult(cur, cur, x);
			if (cur == x - 1) {
				good = true;
				break;
			}  
		}

		if (!good)
			return false;
	}
	return true;
}
