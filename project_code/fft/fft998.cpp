const int LOG = 20;
const int N = 1 << LOG;
const int NN = N + 5;

int bitrev[NN];
M w[NN];

#warning call initfft
bool init_was_called = false;
void initfft() {
    init_was_called = true;
    int W = 2;
    while (true) {
        M x = W;
        for (int i = 1; i < LOG; ++i) {
            x *= x;
        }
        if (x + 1 == M(0)) break;
        ++W;
    }
    w[0] = 1;
    for (int i = 1; i < N; ++i) {
        bitrev[i] = (bitrev[i >> 1] >> 1) ^ ((i & 1) << (LOG - 1));
        w[i] = w[i - 1] * W;
    }
}


void fft(vector<M> &a, int k) {
    assert(init_was_called);
    int L = 1 << k;
    for (int i = 0; i < L; ++i) {
        int x = bitrev[i] >> (LOG - k);
        if (x > i) {
            swap(a[i], a[x]);
        }
    }
    for (int lvl = 0; lvl < k; ++lvl) {
        int len = 1 << lvl;
        for (int i = 0; i < L; i += (len << 1)) {
            for (int j = 0; j < len; ++j) {
                M x = a[i + j];
                M y = w[j << (LOG - 1 - lvl)] * a[i + j + len];
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
}

void invfft(vector<M> & c, int k) {
    fft(c, k);
    int L = 1 << k;
    reverse(c.begin() + 1, c.begin() + L);
    M RL = M(1) / M(L);
    for (auto& x : c) {
        x *= RL;
    }
}

vector<M> mult(vector<M> a, vector<M> b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    int c_size = a.size() + b.size() - 1;
    int k = 0;
    while ((1 << k) + 1 < a.size() + b.size()) {
        ++k;
    }
    int L = 1 << k;
    a.resize(L, 0);
    b.resize(L, 0);
    fft(a, k);
    fft(b, k);
    for (int i = 0; i < L; ++i) {
        a[i] *= b[i];
    }
    invfft(a, k);
    a.resize(c_size);
    return a;
}
