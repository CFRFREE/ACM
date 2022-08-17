#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 5000005
using namespace std;
int n, k, p, a[N], suf[N], pre[N];
int fz;
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
int work(int x)
{
	if (x == 1)return 1;
	return ((int)(p - p / x) * work(p % x) % p);
}
signed main()
{
	n = read(), p = read(), k = read();
	int K = k;
	for (int i = 1; i <= n; i++)
		a[i] = read();
	pre[0] = suf[n + 1] = 1;
	for (int i = 1; i <= n; i++)
		pre[i] = (int)pre[i - 1] * a[i] % p;
	for (int i = n; i >= 1; i--)
		suf[i] = (int)(suf[i + 1] * a[i]) % p;
	for (int i = 1; i <= n; i++)
	{
		fz = (fz + (int)K * pre[i - 1] % p * suf[i + 1]) % p;
		//ans=(ans+(LL)j*pre[i-1]%md*suf[i+1])%md;
		K = (int)(K * k) % p;
	}
	//printf("%d\n", fz);
	printf("%lld\n", (fz * (int)work(pre[n]) % p));
	return 0;
}