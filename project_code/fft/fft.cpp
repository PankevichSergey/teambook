using cd = complex<double>;
const int LOG = 20;
const int N = 1 << LOG;
const int NN = N + 5;

const ld PI = 4 * atan(1);


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
    }
}

vector<ll> mult(const vector<ll> & a, const vector<ll> & b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    int c_size = a.size() + b.size() - 1;
    int k = 0;
    while ((1 << k) + 1 < a.size() + b.size()) {
        ++k;
    }
    int L = 1 << k;
    vector<cd> ac(L, 0);
    vector<cd> bc(L, 0);
    for (int i = 0; i < a.size(); ++i) {
        ac[i] = a[i];
    }
    for (int i = 0; i < b.size(); ++i) {
        bc[i] = b[i];
    }
    fft(ac, k);
    fft(bc, k);
    for (int i = 0; i < L; ++i) {
        ac[i] *= bc[i];
    }
    invfft(ac, k);
    ac.resize(c_size);
    vector<ll> res(c_size, 0);
    for (int i = 0; i < c_size; ++i) {
        res[i] = round(ac[i].real());
    }
    return res;
}
