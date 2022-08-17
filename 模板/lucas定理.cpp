#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 200005
using namespace std;
int jc[N], p;
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
int qpow(int x, int k)
{
	int tep = 1ll;
	while (k)
	{
		if (k & 1ll)
			tep = tep * x % p;
		x = x * x % p;
		k >>= 1ll;
	}
	return tep;
}
int C(int x, int y)
{
	if (x < y)
		return 0;
	return (jc[x] * qpow(jc[x - y], p - 2) % p * qpow(jc[y], p - 2));
}
int lucas(int x, int y)
{
	if (!y)
		return 1;
	return C(x % p, y % p) * lucas(x / p, y / p) % p;
}
void init()
{
	memset(jc, 0, sizeof(jc));
	jc[0] = 1;
	for (int i = 1; i <= p; i++)
		jc[i] = (jc[i - 1] * i) % p;
}
signed main()
{
	int T = read();
	while (T--)
	{
		int n = read(), m = read();
		p = read();
		init();
		printf("%lld\n", lucas(n + m, n));
	}
	return 0;
}