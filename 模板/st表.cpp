#include<bits/stdc++.h>
#define LL long long
#define N 100005
using namespace std;
int n, m, st[N][25], lg[N];
inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))X = X * 10 + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
void init()
{
    for (int i = 1; i < N; i++)
    {
        lg[i] = lg[i - 1];
        if (1 << lg[i] == i)lg[i]++;
    }
}
void ST()
{
    for (int i = 1; i <= n; i++)
        st[i][0] = read();
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int get_max(int L, int R)
{
    int k = lg[R - L + 1] - 1;
    return max(st[L][k], st[R - (1 << k) + 1][k]);
}
int main()
{
    init();
    n = read(), m = read();
    ST();
    while (m--)
    {
        int L = read(), R = read();
        printf("%d\n", get_max(L, R));
    }
    return 0;
}