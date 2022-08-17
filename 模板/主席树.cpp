//静态区间第k小
#include<bits/stdc++.h>
#define LL long long
#define maxn 200005

using namespace std;

int n, m, q, cnt;
int L[maxn << 5], R[maxn << 5], sum[maxn << 5], T[maxn], a[maxn], b[maxn];

inline int build(int l, int r)
{
    int rt = ++cnt;
    sum[rt] = 0;
    if (l < r)
    {
        int mid = (l + r) >> 1;
        L[rt] = build(l, mid);
        R[rt] = build(mid + 1, r);
    }
    return rt;
}

inline int change(int pre, int l, int r, int x)
{
    int rt = ++cnt;
    L[rt] = L[pre], R[rt] = R[pre], sum[rt] = sum[pre] + 1;
    if (l < r)
    {
        int mid = (l + r) >> 1;
        if (x <= mid)L[rt] = change(L[pre], l, mid, x);
        else R[rt] = change(R[pre], mid + 1, r, x);
    }
    return rt;
}

inline int search(int u, int v, int l, int r, int k)
{
    if (l >= r)return l;
    int x = sum[L[v]] - sum[L[u]];
    int mid = (l + r) >> 1;
    if (x >= k)return search(L[u], L[v], l, mid, k);
    else return search(R[u], R[v], mid + 1, r, k - x);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    T[0] = build(1, m);

    for (int i = 1; i <= n; i++)
    {
        int t = lower_bound(b + 1, b + m + 1, a[i]) - b;
        T[i] = change(T[i - 1], 1, m, t);
    }

    while (q--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int t = search(T[x - 1], T[y], 1, m, z);
        printf("%d\n", b[t]);
    }

    return 0;
}

