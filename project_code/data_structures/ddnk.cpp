struct nd {
    int prior, key, sz;
    nd *l, *r;
    nd(int key): prior(rng()), sz(1), key(key), l(nullptr), r(nullptr) {};
};

int getsz(nd * t) {
    if (!t)
        return 0;
    return t->sz;
}


void upd(nd *t) {
    if (t) 
        t->sz = getsz(t->l) + getsz(t->r) + 1;
}

void push(nd *t) {

}

pair<nd*, nd*> split(nd* t, int k) {
    if (!t)
        return {nullptr, nullptr};
    push(t);
    if (getsz(t->l) >= k) {
        auto splited = split(t->l, k);
        t->l = splited.second;
        upd(t);
        return {splited.first, t};
    } else {
        auto splited = split(t->r, k - getsz(t->l) - 1);
        t->r = splited.first;
        upd(t);
        return {t, splited.second};
    }

}

nd* merge(nd* t1, nd* t2) {
    if (!t1)
        return t2;
    if (!t2)
        return t1;

    if (t1->prior > t2->prior) {
        push(t1);
        t1->r = merge(t1->r, t2);
        upd(t1);
        return t1;
    } else {
        push(t2);
        t2->l = merge(t1, t2->l);
        upd(t2);
        return t2;
    }
}

nd* DeleteKth(nd* t, int k) {
    if (getsz(t->l) + 1 == k)
        return merge(t->l, t->r);
    
    if (getsz(t->l) >= k) {
        t->l = DeleteKth(t->l, k);
        upd(t);
        return t;
    } else {
        t->r = DeleteKth(t->r, k - getsz(t->l) - 1);
        upd(t);
        return t;
    }
}

nd* Insert(nd* t, int key, int place) {
    nd *key_node = new nd(key);
    auto splited = split(t, place - 1);
    return merge(merge(splited.first, key_node), splited.second);

}

nd* PushBack(nd* t, int key) {
    nd * key_node = new nd(key);
    return merge(t, key_node);
}

int GetKth(nd *t, int k) {
    auto split1 = split(t, k);
    auto split2 = split(split1.first, k - 1);
    nd* ans_node = split2.second;
    push(ans_node);
    int answer = ans_node->key;
    t = merge(merge(split2.first, ans_node), split1.second);
    return answer;
}

void Print(nd *t) {
    int elem_num = getsz(t);
    rep(i, 1,  elem_num + 1) {
        cout << GetKth(t, i) << ' ';
    }
}
