int f[MX];
int f1[MX];

void calcf() {
	f[0] = 1;
	fi(1, MX)
		f[i] = mult(f[i - 1], i);
	f1[MX - 1] = rev(f[MX - 1]);
	fi1(MX - 1, 0)
		f1[i] = mult(f1[i + 1], i + 1);
}

int C(int n, int k) {
	if (k > n || k < 0 || n < 0)
		return 0;
	return mult(f[n], mult(f1[k], f1[n - k]));
}
