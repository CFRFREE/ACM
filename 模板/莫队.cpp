#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 50005
using namespace std;
int n, m, k, cnt[N], a[N], len;
LL ans[N], ans_tep;
struct Node
{
    int l, r, id, pos;
} ask[N];
inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
inline int cmp(Node x, Node y)
{
    if (x.pos != y.pos)return x.pos < y.pos;
    if (x.pos % 2)return x.r < y.r;
    else return x.r > y.r;
}
void add(int pos)
{
    ans_tep += 2 * cnt[a[pos]] + 1;
    cnt[a[pos]]++;
}
void remove(int pos)
{
    ans_tep += 1 - cnt[a[pos]] * 2;
    cnt[a[pos]]--;
}
int main()
{
    n = read(), m = read(), k = read();
    len = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= m; i++)
    {
        ask[i].l = read(), ask[i].r = read();
        ask[i].id = i;
        ask[i].pos = (ask[i].l - 1) / len + 1;
    }
    sort(ask + 1, ask + m + 1, cmp);
    int L = 0, R = 0;
    for (int i = 1; i <= m; i++)
    {
        while (L < ask[i].l)remove(L++);
        while (L > ask[i].l)add(--L);
        while (R > ask[i].r)remove(R--);
        while (R < ask[i].r)add(++R);
        ans[ask[i].id] = ans_tep;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ans[i] - 1);
    return 0;
}