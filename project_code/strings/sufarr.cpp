const int ALP = 256;

int cnt[MX];
int c[MX];
int cn[MX];
int p[MX];
int pn[MX];
int classes;

void sufarr(str s) {
	s += '#';
    int n = s.size();
    fx(x, s)
        ++cnt[x];
    partial_sum(cnt, cnt + ALP, cnt);
    fi(0, n)
        p[--cnt[s[i]]] = i;
    classes = 1;
    c[p[0]] = 0;
    fi(1, n) {
        if (s[p[i]] != s[p[i - 1]]) ++classes;
        c[p[i]] = classes - 1;
    }
    for (int k = 0; (1 << k) < n; ++k) {
        memset(cnt, 0, classes * sizeof(int));
        fi(0, n) {
            pn[i] = p[i] - (1 << k);
            if (pn[i] < 0)
                pn[i] += n;
            ++cnt[c[i]];
        }
        partial_sum(cnt, cnt + classes, cnt);
        fi1(n, 0)
            p[--cnt[c[pn[i]]]] = pn[i];
        classes = 1;
        cn[p[0]] = 0;
        fi(1, n) {
        	int lw = p[i - 1];
        	int rw = lw + (1 << k);
        	int l = p[i];
        	int r = l + (1 << k);
        	if (rw >= n) rw -= n;
        	if (r >= n) r -= n;

            classes += c[l] != c[lw] || c[r] != c[rw];
            cn[p[i]] = classes - 1;
        }
        memcpy(c, cn, n * sizeof(int));
    }
}
