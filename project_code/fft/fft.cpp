int bitrev[NN];
cd w[NN];

void init() {
    fi(0, N) {
        bitrev[i] = ((i & 1) << (LOG - 1)) ^ (bitrev[i >> 1] >> 1);
        w[i] = complex(cos(2 * PI * i / N), sin(2 * PI * i / N));
    }
}


void fft(vector<cd> & a, int k) {
    int L = 1 << k;
    fi(0, L) {
        int x = bitrev[i] >> (LOG - k);
        if (i > x)
            swap(a[i], a[x]);
    }
    rep(lvl, 0, k) {
        int len = 1 << lvl;
        for (int i = 0; i < L; i += len << 1) {
            fj(0, len) {
                cd x = a[i + j];
                cd y = a[i + j + len] * w[j << (LOG - 1 - lvl)];
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
}

void invfft(vector<cd> & a, int k) {
    fft(a, k);
    int L = 1 << k;
    reverse(a.begin() + 1, a.begin() + L);
    fx(x, a) {
        x /= L;
    }
}

vector<ll> mult(vector<ll> & a,  vector<ll> & b) {
    int k = 0;
    while ((1 << k) < siz(a) + siz(b) - 1)
        ++k;
    int L = 1 << k;
    vector<cd> ac(L);
    vector<cd> bc(L);
    vector<cd> cc(L);
    fi(0, a.size())
        ac[i] = a[i];
    fi(0, b.size())
        bc[i] = b[i];
    fft(ac, k);
    fft(bc, k);
    fi(0, L)
        cc[i] = ac[i] * bc[i];
    invfft(cc, k);
    vector<ll> c(L);
    fi(0, L)
        c[i] = (long long) round(cc[i].real());
    return c;
}
