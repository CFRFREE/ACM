#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
using namespace std;
unordered_map<int, int> M;
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
inline int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}
int qpow(int a, int n, int p)
{
	int res = 1;
	while (n)
	{
		if (n & 1)
			res = (__int128)res * a % p;
		a = (__int128)a * a % p;
		n >>= 1;
	}
	return res;
}
int is_prime(int x)
{
	if (x < 3)
		return x == 2;
	if (x % 2 == 0)
		return 0;
	int A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d = x - 1, r = 0;
	while (d % 2 == 0)
		d /= 2, ++r;
	for (auto a : A)
	{
		int v = qpow(a, d, x);
		if (v <= 1 || v == x - 1)
			continue;
		for (int i = 0; i < r; ++i)
		{
			v = (__int128)v * v % x;
			if (v == x - 1 && i != r - 1)
			{
				v = 1;
				break;
			}
			if (v == 1)
				return 0;
		}
		if (v != 1)
			return 0;
	}
	return 1;
}
int PR(int n)
{
	if (n == 4)
		return 2;
	if (is_prime(n))
		return n;
	while (1)
	{
		int c = rand() % (n - 1) + 1;
		auto f = [=](int x) { return ((__int128)x * x + c) % n; };
		int t = 0, r = 0, p = 1, q;
		do
		{
			for (int i = 0; i < 128; i++)
			{
				t = f(t), r = f(f(r));
				if (t == r || (q = (__int128)p * abs(t - r) % n) == 0)
					break;
				p = q;
			}
			int d = gcd(p, n);
			if (d > 1)
				return d;
		} while (t != r);
	}
}
int max_prime_factor(int x)
{
	if (M.count(x))
		return M[x];
	int fac = PR(x);
	if (fac == x)
		M[x] = x;
	else
		M[x] = max(max_prime_factor(fac), max_prime_factor(x / fac));
	return M[x];
}
void work()
{
	int n = read();
	srand(time(NULL));
	if (is_prime(n))
		puts("Prime");
	else
		printf("%lld\n", max_prime_factor(n));
}
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C:\\Users\\FREE\\Desktop\\1.in", "r", stdin);
#endif
	int T = read();
	while (T--)
		work();
	return 0;
}