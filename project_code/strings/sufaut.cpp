struct SufAut {
    struct nd {
        int pr;
        int s;
        int to[K];
        nd() {
            pr = -1;
            s = -1;
            memset(to, -1, sizeof(to));
        }
    };

    vector<nd> t;

    int Add(int a, char ch) {
        dbg(a, ch);
        int b = t.size();
        t.push_back(nd());
        t[b].pr = a;
        t[b].s = 0;
        while (a != -1) {
            if (t[a].to[ch] == -1) {
                t[a].to[ch] = b;
                a = t[a].s;
                continue;
            }
            int c = t[a].to[ch];
            if (t[c].pr == a) {
                t[b].s = c;
                break;
            }
            int d = t.size();
            t.push_back(nd());
            t[d].pr = a;
            t[d].s = t[c].s;
            t[b].s = t[c].s = d;
            memcpy(t[d].to, t[c].to, sizeof(t[d].to));
            for (; a != -1 && t[a].to[ch] == c; a = t[a].s)
                t[a].to[ch] = d;
            break;
        }
        return b;
    }

    int last;

    void Init() {
        last = 0;
        t.push_back(nd());
    }

    void AddString(string& s) {
        for (char x : s) {
            #warning set K and shift (e.g. - 'a')
            last = Add(last, x - 'a');
        }
    }

    void Build(vector<string>& s) {
        Init();
        for (string& st : s) {
            AddString(st);
        }
    }

    SufAut(vector<string>& s) {
        Build(s);
    }
    SufAut(string& s) {
        vector<string> help = {s};
        Build(help);
    }
    
    bool FindString(string& s) {
        int cur = 0;
        for (char x : s) {
            cur = t[cur].to[x];
            if (cur == -1)
                return false;
        }
        return true;
    }
};
