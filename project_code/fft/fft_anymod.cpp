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
        x =  cd(((long long)round(x.real())) % MOD, 0);
    }
}

void norm(vector<ll> & x) {
    while (siz(x) && !x.back())
        x.ppb;
}

vector<ll> mult(vector<ll> & a, vector<ll> & b) {
    norm(a);
    norm(b);
    int k = 0;
    while ((1 << k) < siz(a) + siz(b) - 1)
        ++k;
    int L = 1 << k;
    vector<vector<cd>> ac(2, vector<cd>(L));
    vector<vector<cd>> bc(2, vector<cd>(L));
    fi(0, siz(a)) {
        ac[0][i] = a[i] & (BASE - 1);
        ac[1][i] = a[i] >> LOGB; 
    }
    fi(0, siz(b)) {
        bc[0][i] = b[i] & (BASE - 1);
        bc[1][i] = b[i] >> LOGB;
    }
    fft(bc[0], k);
    fft(bc[1], k);
    fft(ac[0], k);
    fft(ac[1], k);
    vector<ll> res(L, 0);
    vector<cd> c(L);
    fi(0, 2) {
        fj(0, 2) { 
            rep(len, 0, L)
                c[len] = ac[i][len] * bc[j][len];
            invfft(c, k);
            rep(len, 0, L)
                res[len] = add(res[len], mult(Q[i + j], (int)round(c[len].real()) % MOD));
        }
    }
    norm(res);
    return res;
}
