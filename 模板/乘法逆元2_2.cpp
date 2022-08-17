#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 5000005
using namespace std;
int n, p, k, s[N], t[N], a[N], ans, K;
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
	return (int)(p - p / x) * (work(p % x)) % p;
}
signed main()
{
	n = read(), p = read(), k = read();
	K = k;
	s[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		s[i] = (int)s[i - 1] * a[i] % p;
	}
	t[n] = work(s[n]);
	for (int i = n - 1; i >= 1; i--)
		t[i] = (int)t[i + 1] * a[i + 1] % p;
	for (int i = 1; i <= n; i++)
	{
		ans = (ans + ((((int)t[i] * s[i - 1]) % p) * K) % p) % p;
		K = (int)(K * k) % p;
	}
	// for(int i=n;i;--i)
	//      ans=((ll)t[i]*s[i-1]%p+ans)*k%p;
	printf("%lld\n", ans);
	return 0;
}