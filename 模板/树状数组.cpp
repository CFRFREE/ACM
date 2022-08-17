#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 500005
using namespace std;
int n, m, tree[N];
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
inline int lowbit(int x)
{
	return x & -x;
}
void add(int x, int k)
{
	while (x <= n)
	{
		tree[x] += k;
		x += lowbit(x);
	}
}
int sum(int x)
{
	int s = 0;
	while (x)
	{
		s += tree[x];
		x -= lowbit(x);
	}
	return s;
}
signed main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		int x = read();
		add(i, x);
	}
	while (m--)
	{
		int opt = read(), x = read(), y = read();
		if (opt == 1)
			add(x, y);
		else
			printf("%lld\n", sum(y) - sum(x - 1));
	}
	return 0;
}