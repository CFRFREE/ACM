#include <bits/stdc++.h>
#define P 1000000007
#define INF ((1 << 31) - 1)
#define INFF ((1 << 63) - 1)
#define int long long
#define N 1000003
using namespace std;
int jc[N], jc_inv[N];
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch))
	{
		w |= ch == '-';
		ch = getchar();
	}
	while (isdigit(ch))
		X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
int qpow(int x, int y)
{
	int res = 1ll;
	x %= P;
	while (y)
	{
		if (y & 1ll)
			res = res * x % P;
		x = x * x % P;
		y >>= 1ll;
	}
	return res;
}
void init()
{
	jc[0] = 1;
	for (int i = 1; i < N; i++)
		jc[i] = (jc[i - 1] * i) % P;
	jc_inv[N - 1] = qpow(jc[N - 1], P - 2);
	for (int i = N - 1; i >= 1; i--)
		jc_inv[i - 1] = (jc_inv[i] * i) % P;
}
int C(int x, int y)
{
	if (x < y || y < 0)
		return 0;
	if (y == 0)
		return 1;
	return (jc[x] * jc_inv[y] % P) * jc_inv[x - y] % P;
}
signed main()
{
	int T = read();
	init();
	for (int t = 1; t <= T; t++)
	{
		int n = read(), m = read();
		printf("%lld\n", C(n, m));
	}
	return 0;
}
