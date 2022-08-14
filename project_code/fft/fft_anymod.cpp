const int MOD = 1'000'000'007;

inline int mult(int x, int y) {
    return 1ll * x * y % MOD;
}

inline int add(int x, int y) {
    x += y;
    if (x >= MOD) return x - MOD;
    return x;
}

const int LOG = 20;
const int N = 1 << LOG;
const int NN = N + 5;

const int BASE = 1 << 15;
const int LOGB = 15;
const int Q[]{1, BASE, static_cast<int>(1ll * BASE * BASE % MOD)};
const ld PI = 4 * atan(1);
using cd = complex<long double>;


int bitrev[NN];
cd w[NN];


#warning call initfft
bool init_was_called = false;
void initfft() {
    init_was_called = true;
    for (int i = 0; i < N; ++i) {
        bitrev[i] = ((i & 1) << (LOG - 1)) ^ (bitrev[i >> 1] >> 1);
        w[i] = complex(cos(2 * PI * i / N), sin(2 * PI * i / N));
    }
}

void fft(vector<cd> & a, int k) {
    assert(init_was_called);
    int L = 1 << k;
    for (int i = 0; i < L; ++i) {
        int x = bitrev[i] >> (LOG - k);
        if (i > x) {
            swap(a[i], a[x]);
        }
    }
    for (int lvl = 0; lvl < k; ++lvl) {
        int len = 1 << lvl;
        for (int i = 0; i < L; i += len << 1) {
            for (int j = 0; j < len; ++j) {
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
    for (auto &x : a) {
        x /= L;
        x =  cd(((long long)round(x.real())) % MOD, 0);
    }
}

vector<ll> mult(const vector<ll> & a, const vector<ll> & b) {
    if (a.empty() && b.empty()) {
        return {};
    }
    int nsz = a.size() + b.size() - 1;
    int k = 0;
    while ((1 << k) < nsz) {
        ++k;
    }
    int L = 1 << k;
    vector<vector<cd>> aa(2, vector<cd>(L, cd(0, 0)));
    vector<vector<cd>> bb(2, vector<cd>(L, cd(0, 0)));
    for (int i = 0; i < a.size(); ++i) {
        aa[0][i] = a[i] & (BASE - 1);
        aa[1][i] = a[i] >> LOGB;
    }
    for (int i = 0; i < b.size(); ++i) {
        bb[0][i] = b[i] & (BASE - 1);
        bb[1][i] = b[i] >> LOGB;
    }
    fft(bb[0], k);
    fft(bb[1], k);
    fft(aa[0], k);
    fft(aa[1], k);
    vector<ll> res(L, 0);
    vector<cd> c(L);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int len = 0; len < L; ++len) {
                c[len] = aa[i][len] * bb[j][len];
            }
            invfft(c, k);
            for (int len = 0; len < L; ++len) {
                res[len] = add(res[len], mult(Q[i + j], (long long)round(c[len].real()) % MOD));
            }
        }
    }
    res.resize(a.size() + b.size() - 1, 0);
    return res;
}
