int bitrev[NN];
int w[NN];

void init() {
    int W = 2;
    while (true) {
        ll x = W;
        fi(1, LOG)
            x = mult(x, x);
        if (x == MOD - 1) break;
        ++W;
    }
    w[0] = 1;
    fi(1, N) {
        bitrev[i] = (bitrev[i >> 1] >> 1) ^ ((i & 1) << (LOG - 1));
        w[i] = mult(w[i - 1], W);
    }
}


void fft(vi &a, int k) {
    int L = 1 << k;
    fi(0, L) {
        int x = bitrev[i] >> (LOG - k);
        if (x > i) {
            swap(a[i], a[x]);
        }
    }
    rep(lvl, 0, k) {
        int len = 1 << lvl;
        for (int i = 0; i < L; i += (len << 1)) {
            fj(0, len) {
                int x = a[i + j];
                int y = mult(w[j << (LOG - 1 - lvl)], a[i + j + len]);
                a[i + j] = add(x, y);
                a[i + j + len] = sub(x, y);
            }
        }
    }
}

void invfft(vi & c, int k) {
    fft(c, k);
    int L = 1 << k;
    reverse(c.begin() + 1, c.begin() + L);
    int RL = rev(L);
    fx(x, c)
        x = mult(x, RL);
}

vi mult(vi a, vi b) {
    int k = 0;
    while ((1 << k) < siz(a) + siz(b) - 1)
        ++k;
    int L = 1 << k;
    a.resize(L, 0);
    b.resize(L, 0);
    fft(a, k);
    fft(b, k);
    vi c(L);
    fi(0, L)
        c[i] = mult(a[i], b[i]);
    invfft(c, k);
    return c;
}
