/*
 https://cses.fi/problemset/task/1138
 Path Queries
 practice with Dukkha
 */
#include <stdio.h>

#define N    200000

struct L {
    struct L *next;
    int j;
} aa[N];

int xx[N], ll[N], rr[N];
long long tt[N];

void link(int i, int j) {
    static struct L ll_[N * 2], *l = ll_;
    
    l->j = j;
    l->next = aa[i].next; aa[i].next = l++;
}

void dfs(int p, int i) {
    static int t;
    struct L *l;
    
    ll[i] = t++;
    for (l = aa[i].next; l; l = l->next)
        if (l->j != p)
            dfs(i, l->j);
    rr[i] = t;
}

void update(int i, int n, int x) {
    while (i < n) {
        tt[i] += x;
        i |= i + 1;
    }
}

long long query(int i) {
    long long sum = 0;
    
    while (i >= 0) {
        sum += tt[i];
        i &= i + 1;
        i--;
    }
    return sum;
}

int main() {
    static int xx[N];
    int n, q, h, i, j;
    
    scanf("%d%d", &n, &q);
    for (i = 0; i < n; i++)
        scanf("%d", &xx[i]);
    for (h = 0; h < n - 1; h++) {
        scanf("%d%d", &i, &j), i--, j--;
        link(i, j), link(j, i);
    }
    dfs(-1, 0);
    for (i = 0; i < n; i++) {
        update(ll[i], n, xx[i]);
        update(rr[i], n, -xx[i]);
    }
    while (q--) {
        int t, i, x;
        
        scanf("%d%d", &t, &i), i--;
        if (t == 1) {
            scanf("%d", &x);
            update(ll[i], n, x - xx[i]);
            update(rr[i], n, xx[i] - x);
            xx[i] = x;
        } else
            printf("%lld\n", query(ll[i]));
    }
    return 0;
}
